/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:59 by dpiedra           #+#    #+#             */
/*   Updated: 2021/05/14 23:00:37 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			ft_write_com(t_data *data, t_line *line)
{
	if (line->length >= (data->end - 11))
		tputs(data->cl, 1, mini_putchar);
	else
		tputs(data->del, 1, mini_putchar);
	if (data->echo)
		ft_putstr_fd(data->echo, 1);
	ft_putstr_fd("minishell> ", 1);
	write(1, line->com, ft_strlen(line->com));
}

void			check_status(t_line *line)
{
	if (g_gl->status == 130)
	{
		free(line->com);
		line->com = strdup("\0");
		line->length = 0;
		g_gl->status = 0;
	}
}

unsigned long	ul_testcheck(int test, unsigned long a, unsigned long b)
{
	return ((unsigned long)test_check(test, (void *)a, (void *)b));
}
