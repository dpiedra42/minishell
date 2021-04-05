/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:44:38 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/05 16:38:34 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**make_paths(int id, t_data *data, char *input)
{
	char	*str;
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	str = ft_strdup(&data->env[id][5]);
	paths = ft_split(str, ':');
	free(str);
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], input);
		free(tmp);
		i++;
	}
	return (paths);
}

int		exec_2(char **inputs, t_data *data)
{
	int			i;
	char		**paths;
	int			id;
	struct stat	stats;

	i = 0;
	stats.st_mode = 0;
	id = env_index("PATH=", data);
	paths = makepaths(index, data, inputs[0]);
	while (paths[i])
	{
		stat(paths[i], &stats);
		if ((stats.st_mode & S_IXUSR) &&
		(execve(paths[i], inputs, data->env) != -1))
			return (0);
		i++;
	}
	free_env(paths);
	return (1);
}

int		exec(char **inputs, t_data *data)
{
	int			id;
	struct stat	stats;

	stats.st_mode = 0;
	id = env_index("PATH=", data);
	stat(inputs[0], &stats);
	if (ft_strchr(inputs[0], '/') && (stats.st_mode & S_IXUSR) &&
	(execve(inputs[0], &inputs[0], data->env) != -1))
		return (0);
	else if (id >= 0)
	{
		if (!exec_2(inputs, data))
			return (0);
	}
	return (1);
}

void	ft_exec(char **inputs, t_data *data)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!check_exec(inputs, data))
		return (ft_error("\t\tminishell: Unknown command\n", 127));
	pid = fork();
	if (pid == 0)
	{
		if (exec(inputs, data) != 0)
			exit(errno);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		signal_exec();
		waitpid(pid, &status, 0);
	}
	g_status = WEXITSTATUS(status);
	if (g_quit)
		g_status = 130;
}
