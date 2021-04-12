/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:09:37 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/12 17:19:19 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	read_history(int fd, char **current)
{
	int red;

	red = get_next_line(fd, current);
	while (red > 0)
	{
		current++;
		g_last++;
		if (g_last + 1 == HISTORY_SIZE)
			break;
		red = get_next_line(fd, current);
		if (red == 0)
			free(*current);
	}
}

void		get_history(void)
{
	char	**current;
	int		fd;

	ft_bzero(g_history, HISTORY_SIZE + 1);
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
