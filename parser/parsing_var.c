/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:41:45 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/02 17:24:46 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	add_escape(char *src, char *dst, int *i, int *j)
{
	dst[(*j)++] = '\\';
	dst[(*j)++] = src[(*i)++];
}

static char	*copy_val(char *str)
{
	int		maxlen;
	char	*val;
	int		i;
	int		j;

	maxlen = ft_strlen(str) * 2;
	if (!(val = malloc(sizeof(char) * (maxlen + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == '$' || str[i] == '"' ||
			str[i] == '\'' || str[i] == '>' || str[i] == '<')
			add_escape(str, val, &i, &j);
		else
			val[j++] = str[i++];
	}
	val[j] = '\0';
	return (val);
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
	char	*var_val;
	char	*var_name;
	char	*tmp;
	char	*new_command;

	len = file_len(&(command[0][*i + 1]));
	var_name = ft_substr(*command, *i + 1, len);
	if (len == 1 && command[0][*i + 1] == '?')
		var_val = ft_itoa(g_status);
	else if (len)
		var_val = get_val(var_name, data);
	else
		var_val = ft_strdup("$");
	free(var_name);
	new_command = ft_substr(*command, 0, *i);
	tmp = ft_strjoin(new_command, var_val);
	free(new_command);
	new_command = ft_strjoin(tmp, &(command[0][*i + 1 + len]));
	len = ft_strlen(var_val);
	free(tmp);
	free(var_val);
	free(*command);
	*command = new_command;
	*i += len - 1;
}
