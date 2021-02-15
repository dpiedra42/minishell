/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:42:59 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/15 19:06:14 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_clean_command(char *command)
{
	char	*comline;
	int		len;
	
	len = find_len(command);
	printf("len = %d\n", len);
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
	return (0);
}
