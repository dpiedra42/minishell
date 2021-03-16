/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 13:55:20 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/16 18:06:31 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_into(char *str, int i, char **com, t_data *data)
{
	char	*filename;
	int		fd;
	int		j;

	j = i;
	if (str[j + 1] == ' ')
		j++;
	filename = get_filename(&(str[j + 1]), &j);
	remove_redir_input(com, i, j);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	free(filename);
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
	else if (str[i] == '<' && str[i + 1] != '<')
		redir_from(str, i, com, data);
	else if (str[i] == '>' && str[i + 1] == '>')
		redir_to_append(str, i, com, data);
}

void	redir_quotes(char *str, int *i, char quote)
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

int		ft_redir(char **com, t_data *data)
{
	int		i;
	char	*str;
	char	quote;

	i = -1;
	str = *com;
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
			choose_redir(com, i, data);
			return (1);
		}
		ft_escape(&i, str);
	}
	return (0);
}
