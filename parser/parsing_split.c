/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:50:50 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/06 16:54:06 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_split(char *command, char *new_com, char quote)
{
	while (*command != ' ' && *command)
	{
		if (*command == '\'')
		{
			quote = *(command++);
			while (*command != quote)
				*(new_com++) = *(command++);
			command++;
		}
		else if (*command == '"')
		{
			quote = *(command++);
			while (*command != quote)
			{
				if (*command == '\\' && (*(command + 1) == quote ||
					*(command + 1) == '\\' || *(command + 1) == '$'))
					command++;
				*(new_com++) = *(command++);
			}
			command++;
		}
		else
			*(new_com++) = *(command++);
	}
	*new_com = '\0';
}

static char		*next_input(char *command)
{
	char	quote;
	int		slash_count;

	command--;
	while (*(++command))
	{
		if (*command == '"' || *command == '\'')
		{
			quote = *(command++);
			while (*command != quote)
			{
				slash_count = 0;
				while (*command == '\\' && quote == '"' && ++slash_count)
					command++;
				if (slash_count && !(slash_count % 2))
					command--;
				command++;
			}
		}
		if (*command == ' ')
			return (command + 1);
	}
	return (command);
}

static size_t	string_num(char *command)
{
	int		i;
	char	quote;
	int		slash_count;

	i = 1;
	command--;
	while (*(++command))
	{
		if (*command == '"' || *command == '\'')
		{
			quote = *(command++);
			while (*command != quote)
			{
				slash_count = 0;
				while (*command == '\\' && quote == '"' && ++slash_count)
					command++;
				if (slash_count && !(slash_count % 2))
					command--;
				command++;
			}
		}
		if (*command == ' ')
			i++;
	}
	return (i);
}

char			*new_str(char *command)
{
	int		len;
	char	*new_com;
	char	quote;

	quote = 0;
	len = ft_strlen(command);
	new_com = malloc((len + 1) * sizeof(char));
	if (!new_com)
		exit(EXIT_FAILURE);
	copy_split(command, new_com, quote);
	return (new_com);
}

char			**split_command(char *command)
{
	char	**inputs;
	size_t	count;
	size_t	i;

	count = string_num(command);
	inputs = malloc((count + 1) * sizeof(char *));
	if (!inputs)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < count)
	{
		inputs[i++] = new_str(command);
		if (i > 0 && !inputs[i - 1])
			return (NULL);
		command = next_input(command);
	}
	inputs[i] = NULL;
	return (inputs);
}
