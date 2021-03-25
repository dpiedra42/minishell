/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:48:42 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/23 19:19:05 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parent(char *new_com, t_data *data, int pid, int *fds)
{
	int		oldfd;
	int		status;

	if (waitpid(pid, &status, 0) != pid)
		exit(EXIT_FAILURE);
	free(g_user_input);
	g_user_input = NULL;
	oldfd = dup(0);
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
	ft_parse(new_com, data);
	dup2(oldfd, 0);
	close(oldfd);
}

int		ft_pipe(char *command, char *new_com, t_data *data)
{
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		free(new_com);
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		command_directory(command, data, 1);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		free(command);
		command = NULL;
		ft_parent(new_com, data, pid, fds);
	}
	return (1);
}
