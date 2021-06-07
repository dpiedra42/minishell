/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:33:18 by tpons             #+#    #+#             */
/*   Updated: 2021/06/07 12:52:48 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *error, int status)
{
	g_gl->status = status;
	ft_putstr_fd(error, 2);
}

int	check_num(char *input)
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

void	ft_exit(char **inputs, t_data *data, t_global *g)
{
	g_gl->status = 0;
	if (inputs[1])
	{
		if (check_num(inputs[1]))
		{
			if (inputs[2])
				return (ft_error("\tminishell: too many argument\n", 2));
			g_gl->status = ft_atoi(inputs[1]);
			if (g_gl->status > 255)
				g_gl->status = g_gl->status % 256;
			else if (g_gl->status < 0)
				g_gl->status = 256 + g_gl->status;
		}
		else
			ft_error("\t\tminishell: numeric argument is required\n", 2);
	}
	write_history(g);
	free_env(inputs);
	free_env(data->env);
	free(data->pwd);
	exit(g_gl->status);
}
