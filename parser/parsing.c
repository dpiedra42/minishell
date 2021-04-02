/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:42:59 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/02 17:24:40 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			filter_command(char *command, t_data *data, int pipe)
{
	int i;
	int slash;

	i = 0;
	while (command[i])
	{
		if (command[i] == '"')
		{
			i++;
			while (command[i] != '"')
			{
				slash = 0;
				while (command[i] == '\\' && ++i)
					slash++;
				if (command[i] == '$' && !(slash % 2))
					find_variable(&command, &i, data);
				if (slash && !(slash % 2))
					i--;
				i++;
			}
		}
		if (special_chars(&command, &i, data))
			return (0);
	}
	return (command_directory(command, data, pipe));
}

void		copy_command(char *new_com, char *command)
{
	char	quote;

	while (*command)
	{
		if (*command == ' ' && (*(command + 1) == ' ' ||
			*(command + 1) == '\0'))
			command++;
		else if (*command == '"' || *command == '\'')
		{
			*(new_com++) = *command;
			quote = *(command++);
			copy_inside_quotes(&command, &new_com, quote);
			*(new_com++) = *(command++);
		}
		else if (*command == '\\' && *(command + 1))
			escape_input(&new_com, &command);
		else
			*(new_com++) = *(command++);
	}
	*(new_com) = '\0';
}

static int	find_len(char *command)
{
	int		i;
	char	quote;

	i = 0;
	while (*command)
	{
		if (*command == ' ' && (*(command + 1) == ' ' ||
			*(command + 1) == '\0'))
			command++;
		else if (*command == '\\' && (command += 2))
			i += 4;
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

char		*ft_clean_command(char *command)
{
	char	*new_com;
	int		len;

	while (*command == ' ' && *command)
		command++;
	len = find_len(command);
	if (len == -1)
		return (0);
	if (!(new_com = (char *)malloc(sizeof(char) * (len + 1))))
		exit(EXIT_FAILURE);
	copy_command(new_com, command);
	return (new_com);
}

int			ft_parse(char *command, t_data *data)
{
	char *new_command;

	new_command = ft_clean_command(command);
	g_user_input = NULL;
	if (new_command == 0)
	{
		ft_putstr("Multiline is not supported\n");
		return (0);
	}
	if (!*new_command)
	{
		free(new_command);
		return (0);
	}
	return (filter_command(new_command, data, 0));
}