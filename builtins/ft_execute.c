/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:01:07 by tpons             #+#    #+#             */
/*   Updated: 2021/04/12 17:04:35 by dpiedra          ###   ########.fr       */
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
	int			r;
	struct stat	stats;

	i = 0;
	stats.st_mode = 0;
	r = 0;
	stat(inputs[0], &stats);
	if (ft_strchr(inputs[0], '/') && (stats.st_mode & S_IXUSR) &&
	!(stats.st_mode & __S_IFDIR))
		r = 1;
	else
		r = check_path(inputs, data);
	return (r);
}

int		exec_2(char **inputs, t_data *data)
{
	int			i;
	char		**path;
	int			id;
	struct stat	stats;

	i = 0;
	stats.st_mode = 0;
	id = env_index("PATH=", data);
	path = make_paths(id, data, inputs[0]);
	while (path[i])
	{
		stat(path[i], &stats);
		if ((stats.st_mode & S_IXUSR) &&
		(execve(path[i], inputs, data->env) != -1))
			return (0);
		i++;
	}
	free_env(path);
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
	int		stat;

	stat = 0;
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
		waitpid(pid, &stat, 0);
	}
	g_status = WEXITSTATUS(stat);
	if (g_quit)
		g_status = 130;
}
