/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:45:17 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/09 18:33:36 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    minishell()
{
	char    *command;
	int     read;

	while (1)
	{
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
	ft_signal();
	minishell();
	return (0);
}
