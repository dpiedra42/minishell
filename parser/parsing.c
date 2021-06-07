/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:45:05 by gsmets            #+#    #+#             */
/*   Updated: 2021/06/07 12:54:46 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_quote(char **command, char **clean_com, char quote)
{
	int	slash;

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

void	copy_command(char *clean_com, char *command)
{
	char	quote;

	while (*command)
	{
		if (*command == ' ' && (*(command + 1) == ' '
				|| *(command + 1) == '\0'))
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

static int	command_len(char *com, int i)
{
	char	quote;

	while (*com)
	{
		if (*com == ' ' && (*(com + 1) == ' ' || *(com + 1) == '\0'))
			com++;
		else if (*com == '\\')
		{
			com += 2;
			if (com)
				i += 4;
		}
		else if (*com == '"' || *com == '\'')
		{
			quote = *(com++);
			quote_len(&com, &i, quote);
			if (!*com)
				return (-1);
			com++;
			i = i + 2;
		}
		else if (com++)
			i++;
	}
	return (i);
}

char	*clean_command(char *command)
{
	int		len;
	char	*clean_com;
	char	*command_start;
	int		i;

	i = 0;
	command_start = command;
	while (*command == ' ' && *command)
		command++;
	len = command_len(command, i);
	if (len == -1)
	{
		free(command_start);
		return (0);
	}
	clean_com = (char *)malloc(sizeof(char) * (len + 1));
	if (!(clean_com))
		exit(EXIT_FAILURE);
	copy_command(clean_com, command);
	free(command_start);
	return (clean_com);
}

int	ft_parse(char *command, t_data *data, t_global *g)
{
	char	*clean_com;
	int		semi;

	clean_com = clean_command(command);
	g_gl->user_input = NULL;
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
	semi = check_semi(clean_com);
	if (semi == -1)
	{
		ft_error("\t\tsyntax error near unexpected token ';;'\n", 2);
		free(clean_com);
		return (0);
	}
	return (parsing_filter(clean_com, data, 0, g));
}
