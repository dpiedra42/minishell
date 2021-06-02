/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:01:40 by dpiedra           #+#    #+#             */
/*   Updated: 2021/05/26 15:54:06 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	put_command(t_data *data, t_line *line, char *command)
{
	if (line->l < ft_strlen(line->com))
		tputs(data->save, 1, mini_putchar);
	if (line->l >= (data->end - 11))
		tputs(data->cl, 1, mini_putchar);
	else
		tputs(data->del, 1, mini_putchar);
	if (data->echo)
		ft_putstr_fd(data->echo, 1);
	ft_putstr_fd("minishell> ", 1);
	write(1, line->com, ft_strlen(line->com));
	if (line->l < ft_strlen(line->com))
	{
		tputs(data->restore, 1, mini_putchar);
		if (command[0] != 127)
			tputs(data->right, 1, mini_putchar);
	}
}

static int	ft_exception(t_line *line, char *command)
{
	char	*tmp;

	if (command[0] == 127)
		return (1);
	else if (command[0] == '\n' || (command[0] == 4 && line->l))
	{
		if (command[0] == '\n')
			write(1, "\n", 1);
		return (0);
	}
	else
	{
		tmp = line->com;
		line->com = ft_add(line->com, line->l, command);
		line->l++;
		free(tmp);
	}
	return (1);
}

static int	ft_edit(t_data *data, t_line *line, char *command)
{
	char	*tmp;

	if ((ft_strlen(line->com) > 0) && line->l == 0)
		return (ft_exception(line, command));
	else if (command[0] == 127)
	{
		tmp = line->com;
		line->com = ft_delete(line->com, line->l--);
		tputs(data->left, 1, mini_putchar);
		free(tmp);
	}
	else if (command[0] == '\n' || (command[0] == 4 && !line->l))
	{
		if (command[0] == '\n')
			write(1, "\n", 1);
		return (0);
	}
	else
	{
		tmp = line->com;
		line->com = ft_add(line->com, line->l++, command);
		free(tmp);
	}
	return (1);
}

static void	start_line(t_line *line)
{
	line->reset = 0;
	line->l = 0;
	line->old_com = NULL;
	line->com = ft_strdup("\0");
}

char	*ft_getline(t_data *data, int *red, t_global *g)
{
	t_line	line;
	char	c[16];

	start_line(&line);
	while (1)
	{
		*red = read(0, c, 16);
		if (*red <= 0)
			break ;
		if (c[0] == '\n')
			*red = -1;
		c[(*red)] = 0;
		check_status(&line);
		if (*red > 1)
		{
			ft_line(data, &line, c, g);
			continue ;
		}
		if ((ft_strlen(line.com) == 0 && c[0] == 127) || (c[0] == 4 && line.l))
			continue ;
		else if (!ft_edit(data, &line, c))
			break ;
		put_command(data, &line, c);
	}
	return (restart_line(data, line, g));
}
