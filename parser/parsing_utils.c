/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:11:02 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/20 17:50:05 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_escape(int *i, char *str)
{
	if (str[(*i)] == '\\')
		(*i)++;
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

void	escape_input(char **clean_com, char **command)
{
	char	quote;

	(*command)++;
	if (**command == '\'')
		quote = '"';
	else
		quote = '\'';
	*((*clean_com)++) = quote;
	*((*clean_com)++) = *((*command)++);
	*((*clean_com)++) = quote;
}
