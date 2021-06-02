/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:09:37 by dpiedra           #+#    #+#             */
/*   Updated: 2021/05/26 14:56:55 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_history(t_global *g)
{
	int			fd;
	int			i;

	fd = open(HISTORY_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	i = 0;
	while (i <= g->last)
	{
		write(fd, g->history[i], ft_strlen(g->history[i]));
		write(fd, "\n", 1);
		free(g->history[i]);
		i++;
	}
	close(fd);
}

void	add_command(char *command, t_global *g)
{
	if (!(command && ft_strlen(command)))
		return ;
	if (g->last >= HISTORY_SIZE - 1)
	{
		free(g->history[0]);
		ft_memmove(g->history, g->history + 1, (HISTORY_SIZE - 1)
			* sizeof(char *));
		g->history[g->last] = ft_strdup(command);
		g->last = HISTORY_SIZE - 1;
	}
	else
		g->history[++g->last] = ft_strdup(command);
}

static void	read_history(int fd, char **current, t_global *g)
{
	int	red;

	red = get_next_line(fd, current);
	while (red > 0)
	{
		current++;
		g->last++;
		if (g->last + 1 == HISTORY_SIZE)
			break ;
		red = get_next_line(fd, current);
		if (red == 0)
			free(*current);
	}
}

void	get_history(t_global *g)
{
	char	**current;
	int		fd;

	ft_memset(g->history, 0, HISTORY_SIZE + 1);
	fd = open(HISTORY_FILE, O_RDONLY);
	g->last = -1;
	if (fd == -1)
		return ;
	current = g->history;
	read_history(fd, current, g);
	if (!ft_strlen(*current))
	{
		free(*current);
		*current = 0;
	}
	close(fd);
}
