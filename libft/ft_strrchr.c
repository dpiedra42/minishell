/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:32:44 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/02 17:12:18 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t i;

	i = ft_strlen(str);
	while (i > 0)
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		else
			i--;
	}
	if (str[0] == c)
		return ((char *)&str[0]);
	else
		return (NULL);
}
