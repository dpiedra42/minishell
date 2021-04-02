/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:49:42 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/02 14:52:49 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_pwd(t_data *data)
{
	char *pwd;

	data->pwd = getcwd(NULL, 0);
	if (env_index(data, "PWD") >= 0)
	{
		pwd = ft_strjoin("PWD=", data->pwd);
		replace_var(pwd, data, env_index(data, pwd));
		free(pwd);
	}
	else
	{
		pwd = ft_strjoin("PWD=", data->pwd);
		data->env = exp_env(data->env, pwd);
		free(pwd);
	}
}

void	set_oldpwd(t_data *data)
{
	char *pwd;
	char *oldpwd;

	if (env_index(data, "OLDPWD") >= 0)
	{
		pwd = ft_strjoin("PWD=", data->pwd);
		oldpwd = ft_strjoin("OLD", pwd);
		replace_var(oldpwd, data, env_index(data, "OLDPWD="));
		free(oldpwd);
		free(pwd);
	}
	else
		data->env = exp_env(data->env, "OLDPWD");
	free(data->pwd);
}

int		change_dir(t_data *data, char *str)
{
	char	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd && str && !ft_strcmp(".", str))
	{
		ft_putstr_fd("Error retrieving current directory\n", 1);
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
