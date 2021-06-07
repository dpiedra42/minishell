/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:04:28 by tpons             #+#    #+#             */
/*   Updated: 2021/06/07 11:28:48 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	*g_gl;

void	ft_eof(t_data *data, char *user_input)
{
	free_env(data->env);
	free(user_input);
	free(data->pwd);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}

int	init_termios(struct termios *backup)
{
	struct termios	tattr;

	if (tcgetattr(STDIN_FILENO, &tattr))
		return (0);
	if (tcgetattr(STDIN_FILENO, backup))
		return (0);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tattr))
		return (0);
	return (1);
}

void	minishell(t_data *data, t_global *g)
{
	struct termios	backup;
	int				red;

	red = 0;
	while (1)
	{
		if (!init_termios(&backup))
			return ;
		g_gl->quit = 0;
		free(g_gl->user_input);
		ft_signal();
		ft_putstr_fd("minishell> ", 1);
		g_gl->user_input = ft_getline(data, &red, g);
		if (!reset_terminal(&backup, data))
			return ;
		free(data->echo);
		data->echo = NULL;
		add_command(g_gl->user_input, g);
		if (red == 1)
			ft_eof(data, g_gl->user_input);
		else
			ft_parse(g_gl->user_input, data, g);
	}
}

void	init_data(t_data *data, char **env)
{
	if (tgetent(NULL, getenv("TERM")) <= 0)
		return ;
	data->pwd = getcwd(NULL, 0);
	data->env = copy_env(env);
	data->fd_in = 0;
	data->fd_out = 1;
	data->redir = 1;
	data->echo = NULL;
	data->reset = tgetstr("me", NULL);
	data->del = tgetstr("dl", NULL);
	data->left = tgetstr("le", NULL);
	data->right = tgetstr("nd", NULL);
	data->restore = tgetstr("rc", NULL);
	data->save = tgetstr("sc", NULL);
	data->cl = tgetstr("cl", NULL);
	data->end = tgetnum("co");
}

int	main(int ac, char **av, char **env)
{
	t_data		data;
	t_global	g;

	ac = 0;
	av = NULL;
	g_gl = malloc(sizeof(t_vars));
	if (!(g_gl))
		exit(EXIT_FAILURE);
	init_data(&data, env);
	g_gl->status = 0;
	g_gl->user_input = NULL;
	if (!data.env)
		exit(EXIT_FAILURE);
	get_history(&g);
	minishell(&data, &g);
	return (0);
}
