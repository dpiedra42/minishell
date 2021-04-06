/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:19:01 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/06 15:20:58 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	escape_input(char **new_com, char **command)
{
	char	quote;

	(*command)++;
	if (**command == '\'')
		quote = '"';
	else
		quote = '\'';
	*((*new_com)++) = quote;
	*((*new_com)++) = *((*command)++);
	*((*new_com)++) = quote;
}

void	copy_quote(char **command, char **new_com, char quote)
{
	int slash;

	while (**command != quote)
	{
		slash = 0;
		while (**command == '\\' && quote == '"')
		{
			*((*new_com)++) = *((*command)++);
			slash++;
		}
		if (slash && !(slash % 2))
			*((*new_com)--) = *((*command)--);
		*((*new_com)++) = *((*command)++);
	}
}

void	quote_len(char **command, int *i, char quote)
{
	int slash;

	while (**command != quote && **command)
	{
		slash = 0;
		while (quote == '"' && **command == '\\')
		{
			(*i)++;
			(*command)++;
			slash++;
		}
		if (slash && !(slash % 2))
		{
			(*command)--;
			(*i)--;
		}
		(*i)++;
		(*command)++;
	}
}
