/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:11:02 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/07 14:03:17 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			quote_len(char **command, int *i, char quote)
{
	int slash_count;

	while (**command != quote && **command)
	{
		slash_count = 0;
		while (quote == '"' && **command == '\\')
		{
			(*i)++;
			(*command)++;
			slash_count++;
		}
		if (slash_count && !(slash_count % 2))
		{
			(*command)--;
			(*i)--;
		}
		(*i)++;
		(*command)++;
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
