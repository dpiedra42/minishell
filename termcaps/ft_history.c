/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:09:37 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/28 14:15:22 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		write_history(void)
{
	int		fd;
	int		i;

	fd = open(HISTORY_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	i = 0;
	while (i <= g_last)
	{
		write(fd, g_history[i], ft_strlen(g_history[i]));
		write(fd, "\n", 1);
		free(g_history[i]);
		i++;
	}
	close(fd);
}

void		add_command(char *command)
{
	if (!(command && ft_strlen(command)))
		return ;
	if (g_last >= HISTORY_SIZE - 1)
	{
		free(g_history[0]);
		ft_memmove(g_history, g_history + 1, (HISTORY_SIZE - 1)
			* sizeof(char *));
		g_history[g_last] = ft_strdup(command);
		g_last = HISTORY_SIZE - 1;
	}
	else
		g_history[++g_last] = ft_strdup(command);
}

static void	read_history(int fd, char **current)
{
	int red;

	red = get_next_line(fd, current);
	while (red > 0)
	{
		current++;
		g_last++;
		if (g_last + 1 == HISTORY_SIZE)
			break ;
		red = get_next_line(fd, current);
		if (red == 0)
			free(*current);
	}
}

void		get_history(void)
{
	char	**current;
	int		fd;

	ft_memset(g_history, 0, HISTORY_SIZE + 1);
	fd = open(HISTORY_FILE, O_RDONLY);
	g_last = -1;
	if (fd == -1)
		return ;
	current = g_history;
	read_history(fd, current);
	if (!ft_strlen(*current))
	{
		free(*current);
		*current = 0;
	}
	close(fd);
}
