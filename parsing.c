/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:42:59 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/05 16:00:26 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_create_commands(char *command)
{
	char **comlines;
	t_parse p;

	p.num_commands = count_commands(command, ";");
	comlines = (char**)malloc(sizeof(char*) * p.num_commands + 1);
	p.i = 0;
	p.h = 0;
	while (p.h <= (p.num_commands + p.num_commands - 1))
	{
		p.j = 0;
		p.len = count_chars(command, ";");
		printf("len = %d\n", p.len);
		if (command && p.len == 0)
			command++;
		if (command && p.len > 0)
		{
			comlines[p.i] = ft_makestr(p.len);
			while(*command && p.j < p.len && p.len > 0)
				comlines[p.i][p.j++] = *(command++);
			p.i++;
		}
		p.h++;
	}
	comlines[p.i] = NULL;
	return (comlines);
}

 void    ft_parse(char *command)
{
	char **new_commands;

	new_commands = ft_create_commands(command);
}
