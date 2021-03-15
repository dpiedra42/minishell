/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 17:05:46 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/15 17:52:41 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_sigiq(int sig)
{
	if (sig == SIGINT)
	{
		if (g_user_input)
			free(g_user_input);
		g_status = 130;
		g_quit = 1;
		write(2, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_status = 131;
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

void	ft_sigiq(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		if (g_user_input)
			ft_putstr_fd("\nminishell> ", 1);
		if (g_user_input)
			free(g_user_input);
		g_user_input = ft_strdup("\0");
	}
	else if (sig == SIGQUIT)
		write(2, "\b\b  \b\b", 6);
}

void	ft_signal(void)
{
	if (signal(SIGINT, ft_sigiq) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, ft_sigiq) == SIG_ERR)
		exit(EXIT_FAILURE);
}
