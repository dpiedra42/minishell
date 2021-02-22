/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:42:59 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/22 11:24:21 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		command_directory(char *command)
// {
// 	char **inputs;

// 	inputs = split_command(command);
// 	free(command);
// 	choose_builtin(inputs);
// }

int		special_chars(char **command, int *i)
{
	if ((*command)[*i] == '\'')
	{
		(i++);
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

int		filter_command(char *command)
{
	int i;
	int slash;

	i = 0;
	while (command[i])
	{
		if (command[i] = '"')
		{
			i++;
			while (command[i] != '"')
				i++;
		}
		if (special_chars(&command, &i))
			return (0);
	}
	return (command_directory(command));
}

char	*ft_clean_command(char *command)
{
	char	*comline;
	int		len;
	
	len = find_len(command);
	if (len == -1)
		return (0);
	if (!(comline = malloc(sizeof(char) * (len + 1))))
		exit (EXIT_FAILURE);
	copy_command(comline, command);
	return (comline);
}

 int    ft_parse(char *command)
{
	char *new_command;

	g_user_input = NULL;
	while(*command == ' ' && *command)
		command++;
	new_command = ft_clean_command(command);
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
	return (filter_command(new_command));
}
