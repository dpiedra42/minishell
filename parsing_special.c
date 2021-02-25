/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:04:11 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/25 15:09:11 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_semi(char *command, int semi)
{
	char	*semi_command;
	int		i;

	i = 0;
	if (command[semi - 1] == ' ')
		i = 1;
	semi_command = ft_strdup(&command[semi + 1]);
	command[semi - i] = '\0';
	command_directory(command);
	if (g_status != 130)
		return(ft_parse(semi_command));
	else
		free(semi_command);
	return (0);
}

int		special_chars(char **command, int *i)
{
	if ((*command)[*i] == '\'')
	{
		(*i)++;
		while ((*command)[*i] != '\'')
			(*i)++;
	}
	else if ((*command)[*i] == ';')
	{
		ft_semi((*command), *i);
		return (1);
	}
	(*i)++;
	return (0);
}