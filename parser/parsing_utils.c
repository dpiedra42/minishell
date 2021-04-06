/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:11:02 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/06 16:37:48 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_escape(int *i, char *str)
{
	if (str[(*i)] == '\\')
		(*i)++;
}

void			quote_len(char **command, int *i, char quote)
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

void			escape_input(char **new_com, char **command)
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
