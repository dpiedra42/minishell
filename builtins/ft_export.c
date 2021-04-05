/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 19:17:43 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/05 15:44:46 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	export_a(t_data *data)
{
	int		i;
	int		j;
	char	**tmp;
	char	*swap;

	i = 0;
	tmp = get_env(data->env);
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

char	**exp_env(char **env, char *exp)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (env_len(env) + 1));
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

void	ft_export(char **inputs, t_data *data)
{
	int	i;
	int	index;

	i = 1;
	if (inputs[i])
	{
		while (inputs[i])
		{
			index = env_index(inputs[i], data);
			if (index >= 0 && check_exp(inputs[i]))
				replace_var(inputs[i], data, index);
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
