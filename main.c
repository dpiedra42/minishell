/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:45:17 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/01 16:02:38 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    minishell(t_data *data)
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
			ft_parse(command, data);
	}
}

void	init_data(t_data *data)
{
	data->pwd = getcwd(NULL, 0);
}

int     main(int ac, char **av)
{
	t_data data;
	
	init_data(&data);
	ac = 0;
	av = NULL;
	minishell(&data);
	return (0);
}
