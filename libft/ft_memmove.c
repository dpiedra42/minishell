/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:59:56 by dpiedra           #+#    #+#             */
/*   Updated: 2021/05/26 15:16:23 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (dst == NULL && src == NULL)
		return (NULL);
	ptr1 = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	if (ptr1 < ptr2)
		while (len--)
			*(ptr1++) = *(ptr2++);
	else
		while (len--)
			*(ptr1 + len) = *(ptr2 + len);
	return (dst);
}
