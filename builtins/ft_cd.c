/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:15:19 by tpons             #+#    #+#             */
/*   Updated: 2021/05/14 22:55:07 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		change_dir(t_data *data, char *input)
{
	char	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd && input && ft_strcmp(".", input) == 0)
	{
		ft_putstr_fd("Error retrieving current directory\n", 2);
		pwd = data->pwd;
		data->pwd = ft_strjoin(pwd, "/.");
		free(pwd);
	}
	if (cwd)
	{
		set_oldpwd(data);
		new_pwd(data);
	}
	free(cwd);
	return (1);
}

int		reg_cd(char **inputs, t_data *data)
{
	if (chdir(inputs[1]) == -1)
		return (0);
	change_dir(data, inputs[1]);
	return (1);
}

int		cd_sign(t_data *data)
{
	if (env_index("OLDPWD=", data) < 0 ||
	chdir((strchr(data->env[env_index("OLDPWD=", data)], '=') + 1)) == -1)
		return (0);
	change_dir(data, NULL);
	return (1);
}

int		cd_empty(t_data *data)
{
	if (env_index("HOME=", data) < 0 ||
	chdir((strchr(data->env[env_index("HOME=", data)], '=') + 1)) == -1)
		return (0);
	change_dir(data, NULL);
	return (1);
}

void	ft_cd(char **inputs, t_data *data)
{
	if (inputs[1] && inputs[2])
		return (ft_error("cd: too many arguments\n", 1));
	else if (!inputs[1])
	{
		if (!cd_empty(data))
			return (ft_error("cd: HOME: is undefined\n", 1));
	}
	else if (ft_strcmp(inputs[1], "-") == 0)
	{
		if (!cd_sign(data))
			return (ft_error("cd: OLDPWD is undefined\n", 1));
	}
	else
	{
		if (!reg_cd(inputs, data))
			return (ft_error("cd: no such file or directory\n", 1));
	}
	g_gl->status = 0;
}
