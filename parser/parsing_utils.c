/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:11:02 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/07 15:04:56 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		should_escape(int *i, char *str)
{
	if (str[(*i)] == '\\')
		(*i)++;
}

void			quote_len(char **str, int *i, char quote)
{
	int slash;

	while (**str != quote && **str)
	{
		slash = 0;
		while (quote == '"' && **str == '\\')
		{
			(*i)++;
			(*str)++;
			slash++;
		}
		if (slash && !(slash % 2))
		{
			(*str)--;
			(*i)--;
		}
		(*i)++;
		(*str)++;
	}
}

void			escape_input(char **dst, char **src)
{
	char	quote;

	(*src)++;
	if (**src == '\'')
		quote = '"';
	else
		quote = '\'';
	*((*dst)++) = quote;
	*((*dst)++) = *((*src)++);
	*((*dst)++) = quote;
}
