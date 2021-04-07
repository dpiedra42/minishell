/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:04:28 by tpons             #+#    #+#             */
/*   Updated: 2021/04/07 14:40:33 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_eof(t_data *data, char *user_input)
{
	free_env(data->env);
	free(user_input);
	free(data->pwd);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}

void	init_data(t_data *data, char **env)
{
	data->env = dup_env(env);
	data->pwd = getcwd(NULL, 0);
	data->fd_in = 0;
	data->fd_out = 1;
	data->redir = 1;
}

int		main(int ac, char **av, char **env)
{
	t_data	data;
	int		gnl;

	ac = 0;
	av = NULL;
	init_data(&data, env);
	g_status = 0;
	g_user_input = NULL;
	if (!data.env)
		exit(EXIT_FAILURE);
	while (1)
	{
		g_quit = 0;
		free(g_user_input);
		sig_init();
		ft_putstr_fd("minishell> ", 2);
		gnl = get_next_line(0, &g_user_input);
		if (!gnl)
			ft_eof(&data, g_user_input);
		else
			ft_parse(g_user_input, &data);
	}
	return (0);
}
