/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:51:09 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/19 19:26:01 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ft_add(char *str, int i, char *c)
{
	char	*substr;
	char	*substr1;
	char	*tmp;

	substr = ft_substr(str, 0, i);
	substr1 = ft_substr(str, i, ft_strlen(str));
	tmp = ft_strjoin(substr, c);
	free(substr);
	substr = ft_strjoin(tmp, substr1);
	free(tmp);
	free(substr1);
	return (substr);
}

char		*ft_delete(char *str, int i)
{
	char	*substr;
	char	*tmp;

	substr = ft_substr(str, 0, i - 1);
	tmp = ft_substr(str, i, ft_strlen(str));
	str = ft_strjoin(substr, tmp);
	free(tmp);
	free(substr);
	return (str);
}

static void	ft_loop_history(t_data *data, t_line *line, int key, int *cur)
{
	if (key == 0)
		*cur = ul_testcheck(*cur == -1, g_last, max_int(*cur - 1, 0));
	else if (key == 1 && *cur != -1)
		*cur += 1;
	if (*cur > g_last)
		*cur = -1;
	if (*cur == -1 && line->old_buff)
	{
		free(line->buffer);
		line->buffer = line->old_buff;
		line->old_buff = NULL;
	}
	else if (*cur != -1)
	{
		if (!line->old_buff)
			line->old_buff = line->buffer;
		else if (line->buffer != line->old_buff)
			free(line->buffer);
		line->buffer = ft_strdup(g_history[*cur]);
	}
	line->cursor = ft_strlen(line->buffer);
	tputs(data->del, 1, mini_putchar);
	ft_putstr_fd("minishell> ", 1);
	write(1, line->buffer, ft_strlen(line->buffer));
}

int			ft_arrow(char *command)
{
	command += 2;
	if ((*command >= 'A' && *command <= 'D'))
	{
		return (*command - 65);
	}
	return (-1);
}

void		ft_line(t_data *data, t_line *line, char *command)
{
	static int	current = -1;
	int			key;

	if (line->reset)
	{
		current = -1;
		return ;
	}
	key = ft_arrow(command);
	if (key == 3 && line->cursor >= 1)
	{
		tputs(data->left, 1, mini_putchar);
		line->cursor--;
	}
	if (key == 2 && line->cursor < ft_strlen(line->buffer))
	{
		tputs(data->right, 1, mini_putchar);
		line->cursor++;
	}
	if (key == 0 || key == 1)
		ft_loop_history(data, line, key, &current);
}
