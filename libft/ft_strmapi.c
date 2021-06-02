/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:59:19 by dpiedra           #+#    #+#             */
/*   Updated: 2021/05/26 15:11:27 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*snew;

	if (!s || !f)
		return (NULL);
	snew = malloc(sizeof(char) * (ft_strlen(s)) + 1);
	if (!(snew))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		snew[i] = (*f)(i, s[i]);
		i++;
	}
	snew[i] = '\0';
	return (snew);
}
