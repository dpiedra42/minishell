/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:35:45 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/02 17:48:25 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit (EXIT_FAILURE);
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
	while(data->env[i])
	{
		ft_putstr_fd(data->env[i], 0);
		write(0, "\n", 1);
		i++;
	}
	g_status = 0;
}