/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:30:40 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/27 16:52:21 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	n;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
	{
		free((char *)s);
		return (NULL);
	}
	n = 0;
	while (len-- && s[start])
	{
		substr[n] = s[start];
		n++;
		start++;
	}
	substr[n] = '\0';
	return (substr);
}
