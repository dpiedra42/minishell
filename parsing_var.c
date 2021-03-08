/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:41:45 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/08 21:24:35 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_len(char *str)
{
	int len;

	len = 0;
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	if (!len && str[len] == '?')
		return (1);
	return (len);
}

static void	add_escaped_char(char *src, char *dst, int *i, int *j)
{
	dst[(*j)++] = '\\';
	dst[(*j)++] = src[(*i)++];
}

static char	*dup_value(char *str)
{
	int		maxlen;
	char	*value;
	int		i;
	int		j;

	maxlen = ft_strlen(str) * 2;
	value = malloc((maxlen + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == '$' || str[i] == '"' ||
			str[i] == '\'' || str[i] == '>' || str[i] == '<')
			add_escaped_char(str, value, &i, &j);
		else
			value[j++] = str[i++];
	}
	value[j] = '\0';
	return (value);
}

static char	*get_val(char *name, t_data *data)
{
	char	**env;
	int		i;
	int		j;

	env = data->env;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=' && env[i][j] == name[j])
			j++;
		if (env[i][j] == '=' && !name[j])
			return (dup_value(&env[i][j + 1]));
		i++;
	}
	return (NULL);
}

void    find_variable(char **command, int *i, t_data *data)
{
	int		len;
	char	*var_value;
	char	*var_name;
	char	*tmp;
	char	*new_command;

	len = var_len(&(command[0][*i + 1]));
	var_name = ft_substr(*command, *i + 1, len);
	if (len == 1 && command[0][*i + 1] == '?')
		var_value = ft_itoa(g_status);
	else if (len)
		var_value = get_val(var_name, data);
	else
		var_value = ft_strdup("$");
	free(var_name);
	new_command = ft_substr(*command, 0, *i);
	tmp = ft_strjoin(new_command, var_value);
	free(new_command);
	new_command = ft_strjoin(tmp, &(command[0][*i + 1 + len]));
	len = ft_strlen(var_value);
	free(tmp);
	free(var_value);
	free(*command);
	*command = new_command;
	*i += len - 1;
}
