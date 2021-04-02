/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:10:08 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/02 17:11:17 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	int count;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return ;
	}
	count = 0;
	while (str[count])
		count++;
	write(1, str, count);
}
