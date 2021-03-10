/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 13:55:20 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/10 15:25:26 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parsing_quotes(char *str, int *i, char quote)
{
	int slash_count;

	while (str[*i] != quote)
	{
		slash_count = 0;
		while (str[*i] == '\\' && quote == '"')
		{
			slash_count++;
			(*i)++;
		}
		if (slash_count && !(slash_count % 2))
			(*i)--;
		(*i)++;
	}
}

int			clean_quotes(char **com)
{
	int		i;
	char	*str;
	char	quote;

	i = -1;
	str = *com;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			parsing_quotes(str, &i, quote);
		}
	}
	return (0);
}
