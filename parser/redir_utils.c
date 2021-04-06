/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:14:30 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/06 17:00:02 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		filename_len(char *str)
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

void		copy_file(char *src, char *dst, int i, int k)
{
	while (src[i] != ' ' && src[i] != '|' && src[i] != ';' && src[i] != '>' &&
			src[i] != '<' && src[i])
	{
		if (src[i] == '\'')
		{
			while (src[++i] != '\'')
				dst[k++] = src[i];
			i++;
		}
		else if (src[i] == '"')
		{
			while (src[++i] != '"')
			{
				if (src[i] == '\\')
					i++;
				dst[k++] = src[i];
			}
			i++;
		}
		else
			dst[k++] = src[i++];
	}
	dst[k] = '\0';
}

void		delete_redir(char **com, int i, int j)
{
	char *tmp;
	char *new_input;

	tmp = ft_substr(com[0], 0, i);
	new_input = ft_strjoin(tmp, &(com[0][j + 1]));
	free(tmp);
	free(*com);
	*com = new_input;
}

char		*get_file(char *str, int *j)
{
	int		i;
	int		k;
	char	*file;

	i = filename_len(str);
	*j += i;
	file = malloc((i + 1) * sizeof(char));
	if (!file)
		return (NULL);
	i = 0;
	k = 0;
	copy_file(str, file, i, k);
	return (file);
}

void	redir_from(char *str, int i, char **com, t_data *data)
{
	char	*file;
	int		fd;
	int		j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	file = get_file(&(str[j + 1]), &j);
	delete_redir(com, i, j);
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
	ft_redir(com, data);
}
