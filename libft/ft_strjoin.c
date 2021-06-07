/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:47:06 by dpiedra           #+#    #+#             */
/*   Updated: 2021/06/07 12:03:02 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoin;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	sjoin = malloc((len1 + len2 + 1) * sizeof(char));
	if (!sjoin)
	{
		free((char *)s1);
		free((char *)s2);
		return (NULL);
	}
	ft_memmove(sjoin, s1, len1);
	ft_memmove(&sjoin[len1], s2, len2);
	sjoin[len1 + len2] = '\0';
	return (sjoin);
}
