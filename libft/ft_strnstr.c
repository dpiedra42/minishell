/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:25:00 by dpiedra           #+#    #+#             */
/*   Updated: 2021/05/26 15:12:44 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0' || !needle)
		return ((char *)haystack);
	if (len == '0' || !len)
		return (NULL);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (needle[j] && haystack[i + j] == needle[j] && (i + j) < len)
			{
				j++;
				if (needle[j] == '\0')
					return ((char *)haystack + i);
			}
		}
		i++;
	}
	return (NULL);
}
