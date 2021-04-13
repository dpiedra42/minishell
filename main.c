/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:04:28 by tpons             #+#    #+#             */
/*   Updated: 2021/04/13 19:01:22 by dpiedra          ###   ########.fr       */
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

int		init_termios(struct termios *backup)
{
	struct termios term_attr;

	if (tcgetattr(STDIN_FILENO, &term_attr))
		return (0);
	if (tcgetattr(STDIN_FILENO, backup))
		return (0);
	term_attr.c_lflag &= ~(ICANON | ECHO);
	term_attr.c_cc[VMIN] = 1;
	term_attr.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term_attr))
		return (0);
	return (1);
}

void	minishell(t_data *data)
{
	char 			*command;
	int				read;
	struct termios	backup;

	while (1)
	{
		if (!init_termios(&backup))
			return ;
		g_quit = 0;
		free(g_user_input);
		ft_signal();
		ft_putstr_fd("minishell> ", 2);
		command = ft_getline(data);
		if (!reset_terminal(&backup, data))
			return ;
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
	
	term = getenv("TERM");
	term = NULL;
	if (!term)
		term = ft_strdup("xterm-256color");
	if (tgetent(NULL, term) <= 0)
		return ;
	free(term);
	data->pwd = getcwd(NULL, 0);
	data->env = copy_env(env);
	data->fd_in = 0;
	data->fd_out = 1;
	data->redir = 1;
	data->reset = tgetstr("reset", NULL);
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
	get_history();
	minishell(&data);
	return (0);
}
