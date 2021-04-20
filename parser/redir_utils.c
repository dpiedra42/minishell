/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:14:30 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/20 17:48:43 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_file(char *str, char *file, int i, int k)
{
	while (str[i] != ' ' && str[i] != '|' && str[i] != ';' && str[i] != '>' &&
			str[i] != '<' && str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				file[k++] = str[i];
			i++;
		}
		else if (str[i] == '"')
		{
			while (str[++i] != '"')
			{
				if (str[i] == '\\')
					i++;
				file[k++] = str[i];
			}
			i++;
		}
		else
			file[k++] = str[i++];
	}
	file[k] = '\0';
}

int		get_file_len(char *str)
{
	int i;

	i = 0;
	while (str[i] != ' ' && str[i] != '|' && str[i] != ';' && str[i] != '>' &&
			str[i] != '<' && str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				;
			i++;
		}
		else if (str[i] == '"')
		{
			while (str[++i] != '"')
			{
				if (str[i] == '\\')
					i++;
			}
			i++;
		}
		else
			i++;
	}
	return (i);
}

char	*get_file(char *str, int *j)
{
	int		i;
	int		k;
	char	*file;

	i = get_file_len(str);
	*j += i;
	if (!(file = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	k = 0;
	make_file(str, file, i, k);
	return (file);
}

void	remove_redir(char **command, int i, int j)
{
	char *tmp;
	char *new_com;

	tmp = ft_substr(command[0], 0, i);
	new_com = ft_strjoin(tmp, &(command[0][j + 1]));
	free(tmp);
	free(*command);
	*command = new_com;
}

void	redir_from(char *str, int i, char **command, t_data *data)
{
	char	*file;
	int		fd;
	int		j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	file = get_file(&(str[j + 1]), &j);
	remove_redir(command, i, j);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Wrong file name or wrong permissions\n", 2);
		g_status = 1;
		data->redir = 0;
		return ;
	}
	dup2(fd, 0);
	if (data->fd_in != 0)
		close(data->fd_in);
	data->fd_in = fd;
	ft_redir(command, data);
}
