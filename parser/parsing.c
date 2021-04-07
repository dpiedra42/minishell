/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:45:05 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/07 15:07:00 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			copy_quote(char **src, char **dst, char quote)
{
	int slash_count;

	while (**src != quote)
	{
		slash_count = 0;
		while (**src == '\\' && quote == '"')
		{
			*((*dst)++) = *((*src)++);
			slash_count++;
		}
		if (slash_count && !(slash_count % 2))
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
			copy_quote(&src, &dst, quote);
			*(dst++) = *(src++);
		}
		else if (*src == '\\' && *(src + 1))
			escape_input(&dst, &src);
		else
			*(dst++) = *(src++);
	}
	*dst = '\0';
}

static int		command_len(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (*str)
	{
		if (*str == ' ' && (*(str + 1) == ' ' || *(str + 1) == '\0'))
			str++;
		else if (*str == '\\' && (str += 2))
			i += 4;
		else if (*str == '"' || *str == '\'')
		{
			quote = *(str++);
			quote_len(&str, &i, quote);
			if (!*str)
				return (-1);
			str++;
			i = i + 2;
		}
		else if (str++)
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
	return (parser_delegator(clean_com, data, 0));
}
