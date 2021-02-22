/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:57:55 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/22 10:35:58 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_newsplit(char *src, char *dst, char quote)
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
			{
				if (*src == '\\' && (*(src + 1) == quote ||
					*(src + 1) == '\\' || *(src + 1) == '$'))
					src++;
				*(dst++) = *(src++);
			}
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
	int		slash_count;

	i = 1;
	str--;
	while (*(++str))
	{
		if (*str == '"' || *str == '\'')
		{
			quote = *(str++);
			while (*str != quote)
			{
				slash_count = 0;
				while (*str == '\\' && quote == '"' && ++slash_count)
					str++;
				if (slash_count && !(slash_count % 2))
					str--;
				str++;
			}
		}
		if (*str == ' ')
			i++;
	}
	return (i);
}

char			split_command(char *str)
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
		if (i > 0 && !inputs[i- 1])
			return (NULL);
	
	}
	inputs[i] = NULL;
	return (inputs);
}