/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:33:18 by tpons             #+#    #+#             */
/*   Updated: 2021/04/07 17:44:09 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *error, int status)
{
	g_status = status;
	ft_putstr_fd(error, 2);
}

int		check_num(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '-')
		i++;
	while (input[i])
	{
		if (!ft_isdigit(input[i]))
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
				return (ft_error("\tminishell: too many argument\n", 2));
			g_status = ft_atoi(inputs[1]);
			if (g_status > 255)
				g_status = 255;
			else if (g_status < 0)
				g_status = 255;
		}
		else
			ft_error("\t\tminishell: numeric argument is required\n", 2);
	}
	free_env(inputs);
	free_env(data->env);
	free(data->pwd);
	exit(g_status);
}
