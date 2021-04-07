/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 13:31:30 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/07 16:00:09 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		redir_error(char *command, int *i, char c)
{
	int count;

	count = 0;
	while (command[(*i)] == c)
	{
		count++;
		(*i)++;
	}
	if ((c == '>' && count > 2) || (c == '<' && count > 1))
		return (1);
	while (command[(*i)] == ' ')
		(*i)++;
	if (!command[(*i)])
		return (1);
	return (0);
}

void	skip_quotes(char *command, int *i)
{
	char quote;

	quote = command[(*i)++];
	while (command[(*i)] != quote)
	{
		if (command[(*i)] == '\\' && quote == '"')
			(*i) += 2;
		else
			(*i)++;
	}
}

int		parsing_error(char *command)
{
	int i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '\\')
			i += 2;
		if (command[i] == '"' || command[i] == '\'')
			skip_quotes(command, &i);
		if (command[i] == '>' || command[i] == '<')
		{
			if (redir_error(command, &i, command[i]))
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
