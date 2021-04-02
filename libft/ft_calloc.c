/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:30:08 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/02 17:08:45 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	unsigned char	*ptr;

	ptr = malloc(n * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, n * size);
	return (ptr);
}
