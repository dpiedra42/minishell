/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:50:16 by tpons             #+#    #+#             */
/*   Updated: 2021/05/14 22:57:15 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parent(char *new_com, t_data *data, int pid, t_global *g)
{
	int		oldfd;
	int		stat;

	if (waitpid(pid, &stat, 0) != pid)
		exit(EXIT_FAILURE);
	free(g_gl->user_input);
	g_gl->user_input = NULL;
	oldfd = dup(0);
	dup2(data->fds[0], 0);
	close(data->fds[0]);
	close(data->fds[1]);
	ft_parse(new_com, data, g);
	dup2(oldfd, 0);
	close(oldfd);
}

int		ft_pipe(char *command, char *new_com, t_data *data, t_global *g)
{
	pid_t	pid;

	if (pipe(data->fds) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		free(new_com);
		dup2(data->fds[1], 1);
		close(data->fds[0]);
		close(data->fds[1]);
		command_directory(command, data, 1, g);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		free(command);
		command = NULL;
		ft_parent(new_com, data, pid, g);
	}
	return (1);
}
