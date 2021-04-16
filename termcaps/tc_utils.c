/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:59 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/16 17:17:59 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned long	ul_testcheck(int test, unsigned long a, unsigned long b)
{
	return ((unsigned long)test_check(test, (void *)a, (void *)b));
}
