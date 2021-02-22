/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:04:11 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/22 10:32:38 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_semi(char *command, int semi)
{
	char	*semi_command;
	int		i;

	i = 0;
	if (command[semi - 1] == ' ')
		i = 1;
	semi_command = ft_strdup(&command[semi + 1]);
	printf("str = %s\n", semi_command);
	command[semi - i] = '\0';
	command_directory(command);
	if (g_status != 130)
		return(ft_parse(semi_command));
	else
		free(semi_command);
	return (0);
}