/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:51:09 by dpiedra           #+#    #+#             */
/*   Updated: 2021/06/02 18:43:40 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_add(char *str, int i, char *c)
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

char	*ft_delete(char *str, int i)
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

static void	ft_loop_history(t_data *data, t_line *line, int *cur, t_global *g)
{
	if (line->key == 0)
		*cur = ul_testcheck(*cur == -1, g->last, max_int(*cur - 1, 0));
	else if (line->key == 1 && *cur != -1)
		*cur += 1;
	if (*cur > g->last)
		*cur = -1;
	if (*cur == -1 && line->old_com)
	{
		free(line->com);
		line->com = line->old_com;
		line->old_com = NULL;
	}
	else if (*cur != -1)
	{
		if (!line->old_com)
			line->old_com = line->com;
		else if (line->com != line->old_com)
			free(line->com);
		line->com = ft_strdup(g->history[*cur]);
	}
	line->l = ft_strlen(line->com);
	ft_write_com(data, line);
}

int	ft_arrow(char *command)
{
	command += 2;
	if ((*command >= 'A' && *command <= 'D'))
	{
		return (*command - 65);
	}
	return (-1);
}

void	ft_line(t_data *data, t_line *line, char *command, t_global *g)
{
	static int	current = -1;

	if (line->reset)
	{
		current = -1;
		return ;
	}
	line->key = ft_arrow(command);
	if (line->key == 3 && line->l >= 1)
	{
		tputs(data->left, 1, mini_putchar);
		line->l--;
	}
	if (line->key == 2 && line->l < ft_strlen(line->com))
	{
		tputs(data->right, 1, mini_putchar);
		line->l++;
	}
	if (line->key == 0 || line->key == 1)
		ft_loop_history(data, line, &current, g);
}
