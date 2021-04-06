/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:13:36 by dpiedra           #+#    #+#             */
/*   Updated: 2019/11/18 14:23:05 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*q;
	int				i;

	p = (unsigned char *)s1;
	q = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (p[i] == q[i])
			i++;
		else
			return (p[i] - q[i]);
	}
	return (0);
}
