/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:05:58 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/02 17:10:17 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *ptr1;
	unsigned char *ptr2;

	if (dest == NULL && src == NULL)
		return (NULL);
	ptr1 = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	while (n--)
		*(ptr1++) = *(ptr2++);
	return (dest);
}
