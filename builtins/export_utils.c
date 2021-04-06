/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:35:31 by tpons             #+#    #+#             */
/*   Updated: 2021/04/06 17:55:35 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_exp(char *input)
{
	int	i;

	i = 0;
	if (ft_isdigit(input[i]))
		return (0);
	while (input[i] && input[i] != '=')
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int		put_exp(char **env)
{
	int	i;
	int j;
	int	sign;

	i = -1;
	while (env[++i])
	{
		sign = 1;
		j = 0;
		ft_putstr("declare -x ");
		while (env[i][j])
		{
			if (env[i][j] == '\\' || env[i][j] == '$' ||
			env[i][j] == '\"')
				write(1, "\\", 1);
			write(1, &env[i][j], 1);
			if (env[i][j] == '=' && sign-- == 1)
				write(1, "\"", 1);
			j++;
		}
		if (sign != 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
	return (1);
}
