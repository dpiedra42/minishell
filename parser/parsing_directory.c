/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_directory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:01:43 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/07 15:47:30 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		choose_builtin(char **inputs, t_data *data)
{
	if (!data->redir)
	{
		data->redir = 1;
		return ;
	}
	if (!ft_strcmp(inputs[0], "echo"))
		handle_echo(inputs);
	else if (!ft_strcmp(inputs[0], "pwd"))
		handle_pwd(data);
	else if (!ft_strcmp(inputs[0], "cd"))
		handle_cd(inputs, data);
	else if (!ft_strcmp(inputs[0], "env"))
		handle_env(data->env);
	else if (!ft_strcmp(inputs[0], "exit"))
		handle_exit(inputs, data);
	else if (!ft_strcmp(inputs[0], "export"))
		handle_export(inputs, data);
	else if (!ft_strcmp(inputs[0], "unset"))
		handle_unset(inputs, data);
	else
	{
		handle_exec(inputs, data);
	}
}

void		free_inputs(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		free(inputs[i]);
		i++;
	}
	free(inputs);
}

void		close_fd(t_data *data)
{
	if (data->fd_in != 0)
	{
		close(data->fd_in);
		data->fd_in = 0;
	}
	if (data->fd_out != 1)
	{
		close(data->fd_out);
		data->fd_out = 1;
	}
}

void		pipe_exit(t_data *data)
{
	free_inputs(data->env);
	if (g_user_input)
		free(g_user_input);
	free(data->pwd);
	exit(EXIT_SUCCESS);
}

int			command_directory(char *command, t_data *data, int pipe)
{
	char	**inputs;
	int		oldfd[2];

	if (parsing_error(command))
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
		pipe_exit(data);
	return (0);
}
