/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:50:50 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/07 15:56:42 by dpiedra          ###   ########.fr       */
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

void	copy_split(char *command, char *new_str, char quote)
{
	while (*command != ' ' && *command)
	{
		if (*command == '\'')
		{
			quote = *(command++);
			while (*command != quote)
				*(new_str++) = *(command++);
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
				*(new_str++) = *(command++);
			}
			command++;
		}
		else
			*(new_str++) = *(command++);
	}
	*new_str = '\0';
}

char			*new_strs(char *command)
{
	int		len;
	char	*new_str;
	char	quote;

	quote = 0;
	len = ft_strlen(command);
	if (!(new_str = malloc(sizeof(char) * (len + 1))))
		exit(EXIT_FAILURE);
	copy_split(command, new_str, quote);
	return (new_str);
}

static size_t	string_num(char *command)
{
	int		i;
	char	quote;
	int		slash;

	i = 1;
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
			i++;
	}
	return (i);
}

char			**split_command(char *command)
{
	char	**inputs;
	size_t	num;
	size_t	i;

	num = string_num(command);
	if (!(inputs = malloc(sizeof(char *) * (num + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < num)
	{
		inputs[i++] = new_strs(command);
		if (i > 0 && !inputs[i - 1])
			return (NULL);
		command = next_input(command);
	}
	inputs[i] = NULL;
	return (inputs);
}
