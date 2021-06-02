/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_filter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:47:26 by gsmets            #+#    #+#             */
/*   Updated: 2021/05/27 15:51:05 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	special_pipe(char *command, int pipe, t_data *data, t_global *g)
{
	char	*new_com;
	int		space;

	space = 0;
	if (command[pipe - 1] == ' ')
		space = 1;
	new_com = ft_strdup(&command[pipe + 1]);
	command[pipe - space] = '\0';
	return (ft_pipe(command, new_com, data, g));
}

static int	ft_semi(char *command, int semi, t_data *data, t_global *g)
{
	char	*new_com;
	int		space;

	space = 0;
	if (command[semi - 1] == ' ')
		space = 1;
	new_com = ft_strdup(&command[semi + 1]);
	command[semi - space] = '\0';
	command_directory(command, data, 0, g);
	if (g_gl->status != 130)
		return (ft_parse(new_com, data, g));
	else
		free(new_com);
	return (0);
}

int	special_chars(char **command, int *i, t_data *data, t_global *g)
{
	if ((*command)[*i] == '\'')
	{
		(*i)++;
		while ((*command)[*i] != '\'')
			(*i)++;
	}
	else if ((*command)[*i] == '|')
	{
		special_pipe((*command), *i, data, g);
		return (1);
	}
	else if ((*command)[*i] == ';')
	{
		ft_semi((*command), *i, data, g);
		return (1);
	}
	else if ((*command)[*i] == '$')
		find_variable(command, i, data);
	(*i)++;
	return (0);
}

int	parsing_filter(char *command, t_data *data, int piped, t_global *g)
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
		if (special_chars(&command, &i, data, g))
			return (0);
	}
	return (command_directory(command, data, piped, g));
}
