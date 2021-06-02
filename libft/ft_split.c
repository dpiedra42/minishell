/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:30:42 by dpiedra           #+#    #+#             */
/*   Updated: 2021/05/26 15:20:28 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	stringcount(char const *str, char c)
{
	int	i;

	i = 1;
	while (*str == c && *str)
		str++;
	if (!(*str))
		return (0);
	while (*(++str))
	{
		if (*str != c && *(str - 1) == c)
			i++;
	}
	return (i);
}

static char	*newsplit(char const *str, char c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	ptr = malloc((i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memmove(ptr, str, i);
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	count;
	size_t	i;

	if (s == NULL)
		return (NULL);
	count = stringcount(s, c);
	tab = malloc((count + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < count)
	{
		while (*s == c)
			s++;
		tab[i++] = newsplit(s, c);
		if (!(tab))
			return (NULL);
		while (*s != c && *s)
			s++;
	}
	tab[i] = NULL;
	return (tab);
}
