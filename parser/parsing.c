/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:45:05 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/20 17:51:19 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			copy_quote(char **command, char **clean_com, char quote)
{
	int slash;

	while (**command != quote)
	{
		slash = 0;
		while (**command == '\\' && quote == '"')
		{
			*((*clean_com)++) = *((*command)++);
			slash++;
		}
		if (slash && !(slash % 2))
			*((*clean_com)--) = *((*command)--);
		*((*clean_com)++) = *((*command)++);
	}
}

void			copy_command(char *clean_com, char *command)
{
	char	quote;

	while (*command)
	{
		if (*command == ' ' && (*(command + 1) == ' ' ||
			*(command + 1) == '\0'))
			command++;
		else if (*command == '"' || *command == '\'')
		{
			*(clean_com++) = *command;
			quote = *(command++);
			copy_quote(&command, &clean_com, quote);
			*(clean_com++) = *(command++);
		}
		else if (*command == '\\' && *(command + 1))
			escape_input(&clean_com, &command);
		else
			*(clean_com++) = *(command++);
	}
	*clean_com = '\0';
}

static int		command_len(char *command)
{
	int		i;
	char	quote;

	i = 0;
	while (*command)
	{
		if (*command == ' ' && (*(command + 1) == ' '
			|| *(command + 1) == '\0'))
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

char			*clean_command(char *command)
{
	int		len;
	char	*clean_com;
	char	*command_start;

	command_start = command;
	while (*command == ' ' && *command)
		command++;
	len = command_len(command);
	if (len == -1)
		return (0);
	if (!(clean_com = (char *)malloc(sizeof(char) * (len + 1))))
		exit(EXIT_FAILURE);
	copy_command(clean_com, command);
	free(command_start);
	return (clean_com);
}

int				ft_parse(char *command, t_data *data)
{
	char	*clean_com;

	clean_com = clean_command(command);
	g_user_input = NULL;
	if (clean_com == 0)
	{
		ft_putstr("This minishell does not support multiline\n");
		return (0);
	}
	if (!*clean_com)
	{
		free(clean_com);
		return (0);
	}
	return (parsing_filter(clean_com, data, 0));
}
