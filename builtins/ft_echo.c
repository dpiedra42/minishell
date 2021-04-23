/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:10:26 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/23 17:21:39 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_data *data, char **args)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	g_status = 0;
	data->echo = ft_strdup("\0");
	while (args[i] && !ft_strcmp(args[i], "-n") && i++)
		flag = 1;
	if (flag == 1)
		data->echo = args[i];
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		ft_putstr("\n");
}
