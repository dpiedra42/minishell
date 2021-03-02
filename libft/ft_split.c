/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:30:42 by dpiedra           #+#    #+#             */
/*   Updated: 2019/11/18 14:24:04 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_wordcount(const char *s, char c)
{
	int wordnum;
	int i;

	wordnum = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i + 1] == c && s[i] != c) || (s[i + 1] == '\0' && s[i] != c))
			wordnum++;
		i++;
	}
	return (wordnum);
}

static void		ft_copyword(char **tab, char const *s, char c)
{
	int i;
	int wordlength;
	int strnum;

	i = 0;
	strnum = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			wordlength = 0;
			while (s[i + wordlength] != c && s[i + wordlength] != '\0')
				wordlength++;
			if (!(tab[strnum] =
				(char *)malloc(sizeof(char) * (wordlength + 1))))
				return ;
			tab[strnum] = ft_substr(s, i, wordlength);
			i = i + wordlength;
			strnum++;
		}
	}
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	int		strs;

	if (!s)
		return (NULL);
	strs = ft_wordcount(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (strs + 1))))
		return (NULL);
	tab[strs] = NULL;
	ft_copyword(tab, s, c);
	return (tab);
}
