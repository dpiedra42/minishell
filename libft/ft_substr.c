/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:30:40 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/25 15:16:59 by dpiedra          ###   ########.fr       */
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
	if (!(substr = malloc(sizeof(char) * (len + 1))))
		return (NULL);
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
