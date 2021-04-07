/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:45:05 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/07 14:02:40 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			copy_quotes(char **src, char **dst, char quote)
{
	int slash;

	while (**src != quote)
	{
		slash = 0;
		while (**src == '\\' && quote == '"')
		{
			*((*dst)++) = *((*src)++);
			slash++;
		}
		if (slash && !(slash % 2))
			*((*dst)--) = *((*src)--);
		*((*dst)++) = *((*src)++);
	}
}

void			copy_command(char *dst, char *src)
{
	char	quote;

	while (*src)
	{
		if (*src == ' ' && (*(src + 1) == ' ' || *(src + 1) == '\0'))
			src++;
		else if (*src == '"' || *src == '\'')
		{
			*(dst++) = *src;
			quote = *(src++);
			copy_quotes(&src, &dst, quote);
			*(dst++) = *(src++);
		}
		else if (*src == '\\' && *(src + 1))
			escape_input(&dst, &src);
		else
			*(dst++) = *(src++);
	}
	*dst = '\0';
}

static int		command_len(char *command)
{
	int		i;
	char	quote;

	i = 0;
	while (*command)
	{
		if (*command == ' ' && (*(command + 1) == ' ' || *(command + 1) == '\0'))
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

	while (*command == ' ' && *command)
		command++;
	len = command_len(command);
	if (len == -1)
		return (0);
	clean_com = (char *)malloc((len + 1) * sizeof(char));
	if (!clean_com)
		exit(EXIT_FAILURE);
	copy_command(clean_com, command);
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
	return (parser_delegator(clean_com, data, 0));
}
