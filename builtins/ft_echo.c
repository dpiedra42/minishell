/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:42:53 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/02 17:26:34 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **inputs)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	g_status = 0;
	while (inputs[i] && !ft_strcmp(inputs[i], "-n") && i++)
		flag = 1;
	while (inputs[i])
	{
		write(1, inputs[i], ft_strlen(inputs[i]));
		if (inputs[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
}
