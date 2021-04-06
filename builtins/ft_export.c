/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:35:31 by tpons             #+#    #+#             */
/*   Updated: 2021/04/06 17:46:54 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	replace_var(char *new_var, t_data *data, int id)
{
	if (ft_strchr(new_var, '='))
	{
		free(data->env[id]);
		data->env[id] = ft_strdup(new_var);
	}
}

char	**exp_env(char **env, char *exp)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (e_len(env) + 1));
	if (!new_env)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	free_env(env);
	new_env[i] = ft_strdup(exp);
	i++;
	new_env[i] = NULL;
	return (new_env);
}

void	export_a(t_data *data)
{
	int		i;
	int		j;
	char	**tmp;
	char	*swap;

	i = 0;
	tmp = copy_env(data->env);
	while (tmp[i + 1])
	{
		j = i + 1;
		if (strcmp(tmp[i], tmp[j]) > 0)
		{
			swap = tmp[j];
			tmp[j] = tmp[i];
			tmp[i] = swap;
			i = 0;
		}
		else
			i++;
	}
	put_exp(tmp);
	free_env(tmp);
}

void	ft_export(char **inputs, t_data *data)
{
	int	i;
	int	id;

	i = 1;
	if (inputs[i])
	{
		while (inputs[i])
		{
			id = env_index(inputs[i], data);
			if (id >= 0 && check_exp(inputs[i]))
				replace_var(inputs[i], data, id);
			else if (check_exp(inputs[i]))
			{
				data->env = exp_env(data->env, inputs[i]);
				if (!data->env)
					exit(EXIT_FAILURE);
			}
			else
				return (ft_error("export: bad identifier\n", 1));
			i++;
		}
	}
	else
		export_a(data);
	g_status = 0;
}
