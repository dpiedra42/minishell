/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:57:55 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/25 13:29:28 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*next_input(char *str)
{
	char	quote;

	str--;
	while (*(++str))
	{
		if (*str == '"' || *str == '\'')
		{
			quote = *(str++);
			while (*str != quote)
				str++;
		}
		if (*str == ' ')
			return (str + 1);
	}
	return (str);
}

void			copy_newsplit(char *src, char *dst, char quote)
{
	while (*src != ' ' && *src)
	{
		if (*src == '\'')
		{
			quote = *(src++);
			while (*src != quote)
				*(dst++) = *(src++);
			src++;
		}
		else if (*src == '"')
		{
			quote = *(src++);
			while (*src != quote)
				*(dst++) = *(src++);
			src++;
		}
		else
			*(dst++) = *(src++);
	}
	*dst = '\0';
}

char			*new_str(char *src)
{
	int		len;
	char	*dst;
	char	quote;

	quote = 0;
	len = ft_strlen(src);
	if (!(dst = malloc(sizeof(char) * (len + 1))))
		exit (EXIT_FAILURE);
	copy_newsplit(src, dst, quote);
	return (dst);
}

static size_t	string_len(char *str)
{
	int		i;
	char	quote;

	i = 1;
	str--;
	while (*(++str))
	{
		if (*str == '"' || *str == '\'')
		{
			quote = *(str++);
			while (*str != quote)
				str++;
		}
		if (*str == ' ')
			i++;
	}
	return (i);
}

char			**split_command(char *str)
{
	char **inputs;
	size_t len;
	size_t i;

	len = string_len(str);
	if (!(inputs = malloc(sizeof(char *) * (len + 1))))
		exit (EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		inputs[i++] = new_str(str);
		if (i > 0 && !inputs[i - 1])
			return (NULL);
		str = next_input(str);
	}
	inputs[i] = NULL;
	return (inputs);
}
