/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:04:28 by tpons             #+#    #+#             */
/*   Updated: 2021/04/12 17:21:29 by dpiedra          ###   ########.fr       */
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

void	minishell(t_data *data)
{
	int read;

	while (1)
	{
		g_quit = 0;
		free(g_user_input);
		ft_signal();
		ft_putstr_fd("minishell> ", 2);
		read = get_next_line(0, &g_user_input);
		if (!read)
			ft_eof(data, g_user_input);
		else
			ft_parse(g_user_input, data);
	}
}

void	init_data(t_data *data, char **env)
{
	char 	*term;
	
	data->pwd = getcwd(NULL, 0);
	data->env = copy_env(env);
	data->fd_in = 0;
	data->fd_out = 1;
	data->redir = 1;
	term = getenv("TERM");
	if (tgetent(NULL, term) <= 0)
		exit(EXIT_FAILURE);
	free(term);
	data->left = tgetstr("left", NULL);
	data->right tgetstr("right", NULL);
}

int		main(int ac, char **av, char **env)
{
	t_data	data;

	ac = 0;
	av = NULL;
	init_data(&data, env);
	g_status = 0;
	g_user_input = NULL;
	if (!data.env)
		exit(EXIT_FAILURE);
	get_history
	minishell(&data);
	return (0);
}
