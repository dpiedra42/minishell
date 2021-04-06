/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:57:55 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/02 19:22:50 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char		*next_input(char *command)
{
	char	quote;
	int		slash;

	command--;
	while (*(++command))
	{
		if (*command == '"' || *command == '\'')
		{
			quote = *(command++);
			while (*command != quote)
			{
				slash = 0;
				while (*command == '\\' && quote == '"' && ++slash)
					command++;
				if (slash && !(slash % 2))
					command--;
				command++;
			}
		}
		if (*command == ' ')
			return (command + 1);
	}
	return (command);
}

void			copy_split(char *command, char *new_com, char quote)
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

char			*new_str(char *commands)
{
	int		len;
	char	*new_com;
	char	quote;

	quote = 0;
	len = ft_strlen(commands);
	if (!(new_com = malloc(sizeof(char) * (len + 1))))
		exit(EXIT_FAILURE);
	copy_split(commands, new_com, quote);
	return (new_com);
}

static size_t	string_num(char *commands)
{
	int		i;
	char	quote;
	int		slash;

	i = 1;
	commands--;
	while (*(++commands))
	{
		if (*commands == '"' || *commands == '\'')
		{
			quote = *(commands++);
			while (*commands != quote)
			{
				slash = 0;
				while (*commands == '\\' && quote == '"' && ++slash)
					commands++;
				if (slash && !(slash % 2))
					commands--;
				commands++;
			}
		}
		if (*commands == ' ')
			i++;
	}
	return (i);
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
