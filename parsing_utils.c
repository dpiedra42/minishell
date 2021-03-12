/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:19:01 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/11 16:34:38 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	choose_builtin(char **inputs, t_data *data)
{
	if (!ft_strcmp(inputs[0], "echo"))
		ft_echo(inputs);
	else if (!ft_strcmp(inputs[0], "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(inputs[0], "env"))
		ft_env(data);
	else if (!ft_strcmp(inputs[0], "cd"))
		ft_cd(inputs, data);
	else
		ft_exec(inputs, data);// continue exec tomorrow
}

int		command_directory(char *command, t_data *data, int pipe)
{
	char	**inputs;
	// int		oldfd[2];
	
	// oldfd[0] = dup(1);
	// oldfd[1] = dup(0);
	// command = ft_clean_command(command);
	// clean_quotes(&command);
	// command = ft_clean_command(command);
	inputs = split_command(command);
	free(command);
	choose_builtin(inputs, data);
	free_inputs(inputs);
	// dup2(oldfd[0], 1);
	// dup2(oldfd[1], 0);
	close_fd(data);
	// close(oldfd[0]);
	// close(oldfd[1]);
	if (pipe)
		exit_pipe(data);
	return (0);
}

void	copy_inside_quotes(char **command, char **comline, char quote)
{
	while (**command != quote)
	{
		*((*comline)++) = *((*command)++);
	}
}

void	copy_command(char *comline, char *command)
{
	char	quote;

	while (*command)
	{
		if (*command == ' ' && (*(command + 1) == ' ' ||
			*(command + 1) == '\0'))
			command++;
		else if (*command == '"' || *command == '\'')
		{
			*(comline++) = *command;
			quote = *(command++);
			copy_inside_quotes(&command, &comline, quote);
			*(comline++) = *(command++);
		}
		else if (*command == '\\' && *(command + 1))
			escape_input(&comline, &command);
		else
			*(comline++) = *(command++);
	}
	*(comline) = '\0';
}

void	quote_len(char **command, int *i, char quote)
{
	while (**command != quote && **command)
	{
		(*i)++;
		(*command)++;
	}
}
