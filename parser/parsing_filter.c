/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_filter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:04:11 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/06 15:20:06 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	special_pipe(char *command, int pipe, t_data *data)
{
	char	*new_com;
	int		space;

	space = 0;
	if (command[pipe - 1] == ' ')
		space = 1;
	new_com = ft_strdup(&command[pipe + 1]);
	command[pipe - space] = '\0';
	return (ft_pipe(command, new_com, data));
}

static int	ft_semi(char *command, int semi, t_data *data)
{
	char	*new_com;
	int		space;

	space = 0;
	if (command[semi - 1] == ' ')
		space = 1;
	new_com = ft_strdup(&command[semi + 1]);
	command[semi - space] = '\0';
	command_directory(command, data, 0);
	if (g_status != 130)
		return (ft_parse(new_com, data));
	else
		free(new_com);
	return (0);
}

int			special_chars(char **command, int *i, t_data *data)
{
	if ((*command)[*i] == '\'')
	{
		(*i)++;
		while ((*command)[*i] != '\'')
			(*i)++;
	}
	else if ((*command)[*i] == '|')
	{
		special_pipe((*command), *i, data);
		return (1);
	}
	else if ((*command)[*i] == ';')
	{
		ft_semi((*command), *i, data);
		return (1);
	}
	else if ((*command)[*i] == '$')
		find_variable(command, i, data);
	(*i)++;
	return (0);
}

int			parser_filter(char *command, t_data *data, int pipe)
{
	int		i;
	int		slash;

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