/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:12:18 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/31 12:41:35 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		if (!(*(str + 1)))
			return (i + 1);
		if (!(*(str + 2)))
			return (i + 2);
		if (!(*(str + 3)))
			return (i + 3);
		if (!(*(str + 4)))
			return (i + 4);
		i += 5;
		str += 5;
	}
	return (i);
}
