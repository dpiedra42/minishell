/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:18:29 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/02 17:11:54 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t dest_len;
	size_t src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = dest_len;
	if (dest_len >= size || size == 0)
		return (src_len + size);
	while (*src && i + 1 < size)
	{
		dest[i] = *src;
		src++;
		i++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}
