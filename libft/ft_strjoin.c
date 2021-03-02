/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:47:06 by dpiedra           #+#    #+#             */
/*   Updated: 2019/11/18 14:24:43 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoin;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(sjoin = malloc(sizeof(char) * ((len1 + len2) + 1))))
		return (NULL);
	ft_memmove(sjoin, s1, len1);
	ft_memmove(sjoin + len1, s2, len2);
	sjoin[len1 + len2] = '\0';
	return (sjoin);
}
