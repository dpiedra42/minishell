/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:26:22 by tpons             #+#    #+#             */
/*   Updated: 2021/04/06 17:31:41 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_path(char **inputs, t_data *data)
{
	int			i;
	int			id;
	char		**paths;
	struct stat	stats;

	stats.st_mode = 0;
	i = 0;
	id = env_index("PATH=", data);
	if (env_index("PATH=", data) == -1)
		return (0);
	id = env_index("PATH=", data);
	paths = make_paths(id, data, inputs[0]);
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
