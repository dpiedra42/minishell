/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:49:01 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/05 14:39:30 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str, int status)
{
	g_status = status;
	ft_putstr_fd(str, 0);
}

int		cd_path(char **input, t_data *data)
{
	if (chdir(input[1]) == -1)
		return (0);
	change_dir(data, input[1]);
	return (1);
}

int		cd_minus(t_data *data)
{
	int index;
	
	index = env_index(data, "OLDPWD=");
	if (index == -1 || chdir((strchr(data->env[index], '=') + 1)) == -1 )
		return (0);
	change_dir(data, "-");
	return (1);
}

int		cd_empty(t_data *data)
{
	int index;

	index = env_index(data, "HOME=");
	if (index == -1 || chdir((strchr(data->env[index], '=') + 1)) == -1 )
		return (0);
	change_dir(data, NULL);
	return (1);
}

void	ft_cd(char **input, t_data *data)
{
	if (input[1] && input [2])
		return (ft_error("cd: too many inputs\n", 1));
	else if (!input[1])
	{
		if(!cd_empty(data))
			return (ft_error("cd: HOME not defined\n", 1));
	}
	else if (ft_strcmp(input[1], "-") == 0)
	{
		if (!cd_minus(data))
			return (ft_error("cd: OLDPWD is not defined\n", 1));
	}
	else
	{
		if (!cd_path(input, data))
			return (ft_error("cd: no such file or directory\n", 1));
	}
	g_status = 0;
}
