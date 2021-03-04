/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:35:45 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/04 17:15:00 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_var(char *new_pwd, t_data *data, int index)
{
	if (ft_strchr(new_pwd, '='))
	{
		free(data->env[index]);
		data->env[index] = ft_strdup(new_pwd);
	}
}

int		env_index(t_data *data, char *id)
{
	int i;
	int j;

	i = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j] != '\0' && id[j] != '\0' && data->env[i][j] == id[j] &&
			data->env[i][j] != '=' && id[j] != '=')
			j++;
		if ((data->env[i][j] == '=' && id[j] == '=') ||
			(data->env[i][j] == '\0' && id[j] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int		env_len(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**get_env(char **env)
{
	char	**new_env;
	int		i;
	int		envlen;

	i = 0;
	envlen = env_len(env);
	if (!(new_env = malloc(sizeof(char *) * (envlen + 1))))
		exit(EXIT_FAILURE);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = 0;
	return (new_env);
}

void	ft_env(t_data *data)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		ft_putstr_fd(data->env[i], 0);
		write(0, "\n", 1);
		i++;
	}
	g_status = 0;
}
