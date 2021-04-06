/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:09:15 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/05 16:27:30 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(char **env)
{
	int	i;
	int	e_len;

	i = 0;
	e_len = env_len(env);
	while (i < e_len)
		free(env[i++]);
	free(env);
}

int		check_path(char **inputs, t_data *data)
{
	int			i;
	int			index;
	char		**paths;
	struct stat	stats;

	stats.st_mode = 0;
	i = 0;
	index = env_index("PATH=", data);
	if (env_index("PATH=", data) == -1)
		return (0);
	index = env_index("PATH=", data);
	paths = make_paths(index, data, inputs[0]);
	while (paths[i])
	{
		stat(paths[i], &stats);
		if ((stats.st_mode & S_IXUSR) && !(stats.st_mode & __S_IFDIR))
		{
			free_env(paths);
			return (1);
		}
		i++;
	}
	free_env(paths);
	return (0);
}

int		check_exec(char **inputs, t_data *data)
{
	int			i;
	int			ret;
	struct stat	stats;

	i = 0;
	stats.st_mode = 0;
	ret = 0;
	stat(inputs[0], &stats);
	if (ft_strchr(inputs[0], '/') && (stats.st_mode & S_IXUSR) &&
	!(stats.st_mode & __S_IFDIR))
		ret = 1;
	else
		ret = check_path(inputs, data);
	return (ret);
}
