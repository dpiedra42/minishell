/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:41:45 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/02 18:38:14 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	escape_char(char *src, char *dst, int *i, int *j)
{
	dst[(*j)++] = '\\';
	dst[(*j)++] = src[(*i)++];
}

static char	*copy_val(char *name)
{
	int		maxlen;
	char	*val;
	int		i;
	int		j;

	maxlen = ft_strlen(name) * 2;
	val = malloc((maxlen + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (name[i])
	{
		if (name[i] == '\\' || name[i] == '$' || name[i] == '"' ||
			name[i] == '\'' || name[i] == '>' || name[i] == '<')
			escape_char(name, val, &i, &j);
		else
			val[j++] = name[i++];
	}
	val[j] = '\0';
	return (val);
}

static char	*get_val(char *var_name, t_data *data)
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
		while (env[i][j] && env[i][j] != '=' && env[i][j] == var_name[k])
		{
			k++;
			j++;
		}
		if (env[i][j] == '=' && !var_name[k])
			return (copy_val(&env[i][j + 1]));
		i++;
	}
	return (NULL);
}

static int	file_len(char *command)
{
	int len;

	len = 0;
	while (ft_isalnum(command[len]) || command[len] == '_')
		len++;
	if (!len && command[len] == '?')
		return (1);
	return (len);
}

void		find_variable(char **command, int *i, t_data *data)
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