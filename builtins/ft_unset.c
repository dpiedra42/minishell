/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 19:29:52 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/02 14:26:47 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**unset_env(char **env, int id)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	if (!(new_env = malloc(sizeof(char *) * (env_len(env) - 1))))
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
	int	index;

	i = 1;
	while (inputs[i])
	{
		if (check_exp(inputs[i]))
		{
			index = env_index(data, inputs[i]);
			if (index > 0)
				data->env = unset_env(data->env, index);
			i++;
		}
		else
			return (ft_error("unset: invalid identifier\n", 1));
	}
}
