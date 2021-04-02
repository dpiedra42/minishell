/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:13:23 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/02 18:51:12 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		redir_error(char *command, int *i, char redir)
{
	int count;

	count = 0;
	while (command[(*i)] == redir)
	{
		count++;
		(*i)++;
	}
	if ((redir == '>' && count > 2) || (redir == '<' && count > 1))
		return (1);
	while (command[(*i)] == ' ')
		(*i)++;
	if (!command[(*i)])
		return (1);
	return (0);
}

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

int		parse_error(char *command)
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
