/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:53:53 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/25 15:13:34 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		else
			s++;
	}
	if (c == '\0')
		return ((char *)s);
	else
		return (NULL);
}
