/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:59 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/28 16:15:43 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			check_status(t_line *line)
{
	if (g_status == 130)
	{
		line->length = 0;
		g_status = 0;
	}
}

unsigned long	ul_testcheck(int test, unsigned long a, unsigned long b)
{
	return ((unsigned long)test_check(test, (void *)a, (void *)b));
}
