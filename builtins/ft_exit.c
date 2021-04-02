/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:49:42 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/02 14:31:21 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **inputs, t_data *data)
{
	g_status = 0;
	if (inputs[1])
	{
		if (check_num(inputs[1]))
		{
			if (inputs[2])
				return (ft_error("\tminishell: too many arguments\n", 2));
			g_status = ft_atoi(inputs[1]);
			if (g_status > 255)
				g_status = 255;
			else if (g_status < 0)
				g_status = 255;
		}
		else
			ft_error("\t\tminishell: numeric argument required\n", 2);
	}
	free_env(inputs);
	free(data->pwd);
	free_env(data->env);
	exit(g_status);
}
