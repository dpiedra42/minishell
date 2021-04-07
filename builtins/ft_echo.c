/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:10:26 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/07 17:29:04 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **args)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	g_status = 0;
	while (args[i] && !ft_strcmp(args[i], "-n") && i++)
		flag = 1;
	while (args[i])
	{
		ft_putstr(args[i]);
		//write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		ft_putstr("\n");
		//write(1, "\n", 1);
}
