/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_directory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:20:27 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/06 15:21:01 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	choose_builtin(char **inputs, t_data *data)
{
	if (!data->redir)
	{
		data->redir = 1;
		return ;
	}
	if (!ft_strcmp(inputs[0], "echo"))
		ft_echo(inputs);
	else if (!ft_strcmp(inputs[0], "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(inputs[0], "cd"))
		ft_cd(inputs, data);
	else if (!ft_strcmp(inputs[0], "env"))
		ft_env(data->env);
	else if (!ft_strcmp(inputs[0], "exit"))
		ft_exit(inputs, data);
	else if (!ft_strcmp(inputs[0], "export"))
		ft_export(inputs, data);
	else if (!ft_strcmp(inputs[0], "unset"))
		ft_unset(inputs, data);
	else
	{
		ft_exec(inputs, data);
	}
}

int		command_directory(char *command, t_data *data, int pipe)
{
	char	**inputs;
	int		oldfd[2];

	if (parse_error(command))
	{
		free(command);
		return (0);
	}
	oldfd[0] = dup(1);
	oldfd[1] = dup(0);
	command = clean_command(command);
	ft_redir(&command, data);
	command = clean_command(command);
	inputs = split_command(command);
	free(command);
	choose_builtin(inputs, data);
	free_inputs(inputs);
	dup2(oldfd[0], 1);
	dup2(oldfd[1], 0);
	close_fd(data);
	close(oldfd[0]);
	close(oldfd[1]);
	if (pipe)
		exit_pipe(data);
	return (0);
}