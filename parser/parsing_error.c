/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:13:23 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/02 17:25:22 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		error_redir(char *com, int *i, char c)
{
	int count;

	count = 0;
	while (com[(*i)] == c)
	{
		count++;
		(*i)++;
	}
	if ((c == '>' && count > 2) || (c == '<' && count > 1))
		return (1);
	while (com[(*i)] == ' ')
		(*i)++;
	if (!com[(*i)])
		return (1);
	return (0);
}

void	skip_quotes(char *com, int *i)
{
	char quote;

	quote = com[(*i)++];
	while (com[(*i)] != quote)
	{
		if (com[(*i)] == '\\' && quote == '"')
			(*i) += 2;
		else
			(*i)++;
	}
}

int		parse_error(char *com)
{
	int i;

	i = 0;
	while (com[i])
	{
		if (com[i] == '\\')
			i += 2;
		if (com[i] == '"' || com[i] == '\'')
			skip_quotes(com, &i);
		if (com[i] == '>' || com[i] == '<')
		{
			if (error_redir(com, &i, com[i]))
			{
				g_status = 1;
				ft_putstr_fd("Error: wrong or unsupported redirection\n", 2);
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}