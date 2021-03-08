/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:42:59 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/08 23:21:02 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			filter_command(char *command, t_data *data)
{
	int i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '"')
		{
			i++;
			while (command[i] != '"')
			{
				if (command[i] == '$' && data->e_var == 0)
					find_variable(&command, &i, data);
				i++;
			}
		}
		if (special_chars(&command, &i, data))
			return (0);
	}
	return (command_directory(command, data));
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

char		*ft_clean_command(char *command, t_data *data)
{
	char	*comline;
	int		len;

	len = find_len(command);
	if (len == -1)
		return (0);
	if (!(comline = malloc(sizeof(char) * (len + 1))))
		exit(EXIT_FAILURE);
	copy_command(comline, command, data);
	return (comline);
}

int			ft_parse(char *command, t_data *data)
{
	char *new_command;

	g_user_input = NULL;
	while (*command == ' ' && *command)
		command++;
	new_command = ft_clean_command(command, data);
	if (new_command == 0)
	{
		ft_putstr_fd("Multiline is not supported\n", 1);
		return (0);
	}
	if (!new_command)
	{
		free(new_command);
		return (0);
	}
	return (filter_command(new_command, data));
}
