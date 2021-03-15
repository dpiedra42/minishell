/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:09:15 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/15 18:04:16 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **env)
{
	int	i;
	int	elen;

	i = 0;
	elen = env_len(env);
	while (i < elen)
		free(env[i++]);
	free(env);
}

int		check_path(char **inputs, t_data *data)
{
	int			i;
	int			index;
	char		**paths;
	struct stat	buff;

	buff.st_mode = 0;
	i = 0;
	index = env_index("PATH=", data);
	if (env_index("PATH=", data) == -1)
		return (0);
	index = env_index("PATH=", data);
	paths = make_paths(index, data, inputs[0]);
	while (paths[i])
	{
		stat(paths[i], &buff);
		if ((buff.st_mode & S_IXUSR) && !(buff.st_mode & __S_IFDIR))
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
	struct stat	buff;

	i = 0;
	buff.st_mode = 0;
	ret = 0;
	stat(inputs[0], &buff);
	if (ft_strchr(inputs[0], '/') && (buff.st_mode & S_IXUSR) &&
	!(buff.st_mode & __S_IFDIR))
		ret = 1;
	else
		ret = check_path(inputs, data);
	return (ret);
}
