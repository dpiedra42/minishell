/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:35:13 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/07 15:23:48 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		file_len(char *command)
{
	int len;

	len = 0;
	while (ft_isalnum(command[len]) || command[len] == '_')
		len++;
	if (!len && command[len] == '?')
		return (1);
	return (len);
}

static void		add_escape(char *env, char *value, int *i, int *j)
{
	value[(*j)++] = '\\';
	value[(*j)++] = env[(*i)++];
}

static char		*copy_value(char *env)
{
	int		maxlen;
	char	*value;
	int		i;
	int		j;

	maxlen = ft_strlen(env) * 2;
	value = malloc((maxlen + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (env[i])
	{
		if (env[i] == '\\' || env[i] == '$' || env[i] == '"' ||
			env[i] == '\'' || env[i] == '>' || env[i] == '<')
			add_escape(env, value, &i, &j);
		else
			value[j++] = env[i++];
	}
	value[j] = '\0';
	return (value);
}

static char		*get_val(char *var, t_data *data)
{
	char	**env;
	int		i;
	int		j;
	int		k;

	env = data->env;
	i = 0;
	while (env[i])
	{
		j = 0;
		k = 0;
		while (env[i][j] && env[i][j] != '=' && env[i][j] == var[k])
		{
			k++;
			j++;
		}
		if (env[i][j] == '=' && !var[k])
			return (copy_value(&env[i][j + 1]));
		i++;
	}
	return (NULL);
}

void			find_variable(char **command, int *i, t_data *data)
{
	int		len;
	char	*var_val;
	char	*var_name;
	char	*new_com;
	char	*tmp;

	len = file_len(&(command[0][*i + 1]));
	var_name = ft_substr(*command, *i + 1, len);
	if (len == 1 && command[0][*i + 1] == '?')
		var_val = ft_itoa(g_status);
	else if (len)
		var_val = get_val(var_name, data);
	else
		var_val = ft_strdup("$");
	free(var_name);
	new_com = ft_substr(*command, 0, *i);
	tmp = ft_strjoin(new_com, var_val);
	free(new_com);
	new_com = ft_strjoin(tmp, &(command[0][*i + 1 + len]));
	len = ft_strlen(var_val);
	free(tmp);
	free(var_val);
	free(*command);
	*command = new_com;
	*i += len - 1;
}
