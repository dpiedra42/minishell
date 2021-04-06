/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:03:40 by tpons             #+#    #+#             */
/*   Updated: 2021/04/06 17:46:26 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		env_index(char *id, t_data *data)
{
	int		y;
	int		x;

	x = 0;
	while (data->env[x])
	{
		y = 0;
		while (data->env[x][y] && data->env[x][y] == id[y]
		&& id[y] != '\0' && id[y] != '=' &&
		data->env[x][y] != '\0' && data->env[x][y] != '=')
			y++;
		if ((data->env[x][y] == '\0' || data->env[x][y] == '=') &&
		(id[y] == '\0' || id[y] == '='))
			return (x);
		x++;
	}
	return (-1);
}

void	free_env(char **env)
{
	int	i;
	int	len;

	i = 0;
	len = e_len(env);
	while (i < len)
		free(env[i++]);
	free(env);
}

int		e_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (++i);
}

char	**copy_env(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = malloc(sizeof(char *) * e_len(env));
	if (!new_env)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = 0;
	return (new_env);
}

void	ft_env(char **env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env[i])
	{
		str = ft_strstr(env[i], "=");
		if (str)
		{
			j = 0;
			while (env[i][j])
			{
				write(1, &env[i][j], 1);
				j++;
			}
			ft_putchar('\n');
		}
		i++;
	}
	g_status = 0;
}
