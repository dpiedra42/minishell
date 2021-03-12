/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:04:11 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/12 11:33:40 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*semi_command;
	int		i;

	i = 0;
	if (command[semi - 1] == ' ')
		i = 1;
	semi_command = ft_strdup(&command[semi + 1]);
	command[semi - i] = '\0';
	command_directory(command, data, 0);
	if (g_status != 130)
		return (ft_parse(semi_command, data));
	else
		free(semi_command);
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
	else if ((*command)[*i] == ';')
	{
		ft_semi((*command), *i, data);
		return (1);
	}
	else if ((*command)[*i] == '|')
	{
		special_pipe((*command), *i, data);
		return (1);
	}
	(*i)++;
	return (0);
}
