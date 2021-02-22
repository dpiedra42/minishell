/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:19:01 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/22 11:15:36 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		copy_inside_quotes(char **command, char **comline, char quote)
{
	while (**command != quote)
	{
		if (**command == '\\' && *((*command) + 1) == '\\'  && quote == '"')
			(*command)++;
		*((*comline)++) = *((*command)++);
	}
}

void		copy_command(char *comline, char *command)
{
	char	quote;

	while (*command)
	{
		if (*command == ' ' && (*(command + 1) == ' ' ||
			*(command + 1) == '\0'))
			command++;
		else if (*command == '"' || *command == '\'')
		{
			*(comline++) = *command;
			quote = *(command++);
			copy_inside_quotes(&command, &comline, quote);
			*(comline++) = *(command++);
		}
		else
			*(comline++) = *(command++);
	}
	*(comline) = '\0';
}

void		quote_len(char **command, int *i, char quote)
{
	while (**command != quote && **command)
	{
		(*i)++;
		(*command)++;
	}
}

int	find_len(char *command)
{
	int i;
	char quote;

	i = 0;
	while (*command)
	{
		if (*command == ' ' && (*(command + 1) == ' ' ||
			*(command + 1) == '\0'))
			command++;
		else if (*command == '"' || *command == '\'')
		{
			quote = *(command++);
			quote_len(&command, &i, quote);
			if (!*command)
				return (-1);
			command++;
			i = i + 2;
		}
		else if (command++)
			i++;
	}
	return (i);
}
