/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:41:45 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/23 16:33:01 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	file_len(char *str)
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

static char	*copy_val(char *str)
{
	int		maxlen;
	char	*value;
	int		i;
	int		j;

	maxlen = ft_strlen(str) * 2;
	if (!(value = malloc(sizeof(char) * (maxlen + 1))))
		exit(EXIT_FAILURE);
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
	int		i;
	int		j;
	int		k;
	char	**env;

	i = 0;
	env = data->env;
	while (env[i])
	{
		j = 0;
		k = 0;
		while (env[i][j] && env[i][j] != '=' &&
				env[i][j] == name[k])
		{
			j++;
			k++;
		}
		if (env[i][j] == '=' && !name[k])
			return (copy_val(&env[i][j + 1]));
		i++;
	}
	return (NULL);
}

void		find_variable(char **command, int *i, t_data *data)
{
	int		len;
	char	*v_value;
	char	*v_name;
	char	*tmp;
	char	*new_command;

	len = file_len(&(command[0][*i + 1]));
	v_name = ft_substr(*command, *i + 1, len);
	if (len == 1 && command[0][*i + 1] == '?')
		v_value = ft_itoa(g_status);
	else if (len)
		v_value = get_val(v_name, data);
	else
		v_value = ft_strdup("$");
	free(v_name);
	new_command = ft_substr(*command, 0, *i);
	tmp = ft_strjoin(new_command, v_value);
	free(new_command);
	new_command = ft_strjoin(tmp, &(command[0][*i + 1 + len]));
	len = ft_strlen(v_value);
	free(tmp);
	free(v_value);
	free(*command);
	*command = new_command;
	*i += len - 1;
}
