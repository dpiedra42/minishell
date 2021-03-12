/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:45:17 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/11 16:24:58 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_data *data)
{
	char	*command;
	int		read;

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

void	init_data(t_data *data, char **env)
{
	data->pwd = getcwd(NULL, 0);
	data->env = get_env(env);
	data->fd_in = 0;
	data->fd_out = 1;
	data->redir = 1;
}

int		main(int ac, char **av, char **env)
{
	t_data data;

	init_data(&data, env);
	ac = 0;
	av = NULL;
	minishell(&data);
	return (0);
}
