/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:45:17 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/17 17:17:38 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    minishell()
{
	char    *command;
	int     read;

	g_status = 0;
	g_user_input = NULL;
	while (1)
	{
		g_quit = 0;
		free(g_user_input);
		ft_signal();
		ft_putstr_fd("minishell> ", 1);
		read = get_next_line(0, &command);
		if (!read)
		{
			free(command);
			exit(EXIT_SUCCESS);
		}
		else
			ft_parse(command);
	}
}

int     main(int ac, char **av)
{
	ac = 0;
	av = NULL;
	minishell();
	return (0);
}
