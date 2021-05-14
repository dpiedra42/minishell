/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:32:04 by tpons             #+#    #+#             */
/*   Updated: 2021/05/14 22:57:57 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sigiq(int sig)
{
	if (sig == SIGINT)
	{
		g_gl->status = 130;
		if (g_gl->user_input)
		{
			ft_putstr_fd("^C", 1);
			ft_putstr_fd("\nminishell>", 2);
		}
		else if (!g_gl->user_input)
		{
			ft_putstr_fd("^C\n", 1);
			ft_putstr_fd("minishell>", 2);
		}
		free(g_gl->user_input);
		g_gl->user_input = NULL;
	}
	else if (sig == SIGQUIT)
	{
		if (!g_gl->user_input || g_gl->status == 130)
			return ;
		else
			write(2, "\b\b  \b\b", 6);
	}
}

void	ft_signal(void)
{
	if (signal(SIGINT, ft_sigiq) == SIG_ERR)
		exit(EXIT_FAILURE);
	else if (signal(SIGQUIT, ft_sigiq) == SIG_ERR)
		exit(EXIT_FAILURE);
}

void	exec_sigiq(int sig)
{
	if (sig == SIGINT)
	{
		if (g_gl->user_input)
			free(g_gl->user_input);
		g_gl->status = 130;
		g_gl->quit = 1;
		write(2, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_gl->status = 131;
		ft_putstr_fd("Exit (core dumped)\n", 2);
	}
}

void	signal_exec(void)
{
	if (signal(SIGINT, exec_sigiq) == SIG_ERR)
		exit(EXIT_FAILURE);
	else if (signal(SIGQUIT, exec_sigiq) == SIG_ERR)
		exit(EXIT_FAILURE);
}
