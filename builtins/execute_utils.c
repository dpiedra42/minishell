/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:26:22 by tpons             #+#    #+#             */
/*   Updated: 2021/04/07 18:03:07 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**make_paths(int id, t_data *data, char *input)
{
	char	*str;
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	str = ft_strdup(&data->env[id][5]);
	path = ft_split(str, ':');
	free(str);
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(tmp);
		tmp = path[i];
		path[i] = ft_strjoin(path[i], input);
		free(tmp);
		i++;
	}
	return (path);
}
