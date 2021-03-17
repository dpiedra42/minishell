/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:19:01 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/17 16:53:01 by dpiedra          ###   ########.fr       */
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
	//else if (!ft_strcmp(inputs[0], "export"))
	//	ft_export(inputs, data);
	// else if (!ft_strcmp(inputs[0], "unset"))
	// 	handle_unset(inputs, data);
	else if (!ft_strcmp(inputs[0], "exit"))
		ft_exit(inputs, data);
	else
		ft_exec(inputs, data);
}

int		command_directory(char *command, t_data *data, int pipe)
{
	char	**inputs;

	command = ft_clean_command(command);
	ft_redir(&command, data);
	command = ft_clean_command(command);
	inputs = split_command(command);
	free(command);
	choose_builtin(inputs, data);
	free_inputs(inputs);
	close_fd(data);
	if (pipe)
		exit_pipe(data);
	return (0);
}

void	copy_inside_quotes(char **command, char **comline, char quote)
{
	int slash;

	while (**command != quote)
	{
		slash = 0;
		while (**command == '\\' && quote == '"')
		{
			*((*comline)++) = *((*command)++);
			slash++;
		}
		if (slash && !(slash % 2))
			*((*comline)--) = *((*command)--);
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
	int slash;

	while (**command != quote && **command)
	{
		slash = 0;
		while (quote == '"' && **command == '\\')
		{
			(*i)++;
			(*command)++;
			slash++;
		}
		if (slash && !(slash % 2))
		{
			(*command)--;
			(*i)--;
		}
		(*i)++;
		(*command)++;
	}
}
