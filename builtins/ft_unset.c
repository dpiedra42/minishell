/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:12:35 by tpons             #+#    #+#             */
/*   Updated: 2021/05/05 17:27:20 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**unset_env(char **env, int id)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	if (!(new_env = malloc(sizeof(char *) * (e_len(env) - 1))))
		exit(EXIT_FAILURE);
	while (env[i])
	{
		if (i != id)
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	free_env(env);
	i--;
	new_env[i] = NULL;
	return (new_env);
}

void	ft_unset(char **inputs, t_data *data)
{
	int	i;
	int	id;

	i = 1;
	while (inputs[i])
	{
		if (check_exp(inputs[i]))
		{
			id = env_index(inputs[i], data);
			if (id >= 0)
				data->env = unset_env(data->env, id);
			i++;
		}
		else
			return (ft_error("unset: invalid identifier\n", 1));
	}
}
