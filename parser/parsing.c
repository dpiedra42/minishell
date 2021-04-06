/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:42:59 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/06 15:20:00 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			copy_quote(&command, &new_com, quote);
			*(new_com++) = *(command++);
		}
		else if (*command == '\\' && *(command + 1))
			escape_input(&new_com, &command);
		else
			*(new_com++) = *(command++);
	}
	*new_com = '\0';
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

char		*clean_command(char *command)
{
	int		len;
	char	*new_com;

	while (*command == ' ' && *command)
		command++;
	len = find_len(command);
	if (len == -1)
		return (0);
	new_com = (char *)malloc((len + 1) * sizeof(char));
	if (!new_com)
		exit(EXIT_FAILURE);
	copy_command(new_com, command);
	return (new_com);
}

int			ft_parse(char *command, t_data *data)
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
	return (parser_filter(clean_com, data, 0));
}
