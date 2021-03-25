/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:45:17 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/23 16:11:33 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_end(char *input, t_data *data)
{
	free_env(data->env);
	free(input);
	free(data->pwd);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}

int		minishell(t_data *data)
{
	int		read;

	g_status = 0;
	g_user_input = NULL;
	while (1)
	{
		g_quit = 0;
		free(g_user_input);
		ft_signal();
		ft_putstr_fd("minishell> ", 1);
		read = get_next_line(0, &g_user_input);
		if (!read)
			ft_end(g_user_input, data);
		else
			ft_parse(g_user_input, data);
	}
	return (0);
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
	if (!data.env)
		exit(EXIT_FAILURE);
	ac = 0;
	av = NULL;
	minishell(&data);
	return (0);
}
