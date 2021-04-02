/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 13:55:20 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/02 19:10:59 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_from(char *str, int i, char **com, t_data *data)
{
	char	*file;
	int		fd;
	int		j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	file = get_file(&(str[j + 1]), &j);
	del_redir(com, i, j);
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

void	redir_into(char *str, int i, char **com, t_data *data)
{
	char	*file;
	int		fd;
	int		j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	file = get_file(&(str[j + 1]), &j);
	del_redir(com, i, j);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	free(file);
	if (fd < 0)
	{
		ft_putstr_fd("Error: wrong permissions\n", 2);
		g_status = 1;
		data->redir = 0;
		return ;
	}
	dup2(fd, 1);
	if (data->fd_out != 1)
		close(data->fd_out);
	data->fd_out = fd;
	ft_redir(com, data);
}

void	choose_redir(char **com, int i, t_data *data)
{
	char	*str;
	int		j;

	str = *com;
	j = i;
	if (str[i] == '>' && str[i + 1] != '>')
		redir_into(str, i, com, data);
	else if (str[i] == '>' && str[i + 1] == '>')
		redir_append(str, i, com, data);
	else if (str[i] == '<' && str[i + 1] != '<')
		redir_from(str, i, com, data);
}

void		redir_quotes(char *str, int *i, char quote)
{
	int slash;

	while (str[*i] != quote)
	{
		slash = 0;
		while (str[*i] == '\\' && quote == '"')
		{
			slash++;
			(*i)++;
		}
		if (slash && !(slash % 2))
			(*i)--;
		(*i)++;
	}
}

int		ft_redir(char **command, t_data *data)
{
	int		i;
	char	*str;
	char	quote;

	i = -1;
	str = *command;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			redir_quotes(str, &i, quote);
		}
		if (str[i] == '>' || str[i] == '<')
		{
			choose_redir(command, i, data);
			return (1);
		}
		ft_escape(&i, str);
	}
	return (0);
}
