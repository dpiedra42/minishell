/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:01:40 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/16 18:30:50 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_frame(t_data *data, t_line *line, char *command)
{
	if (line->cursor < ft_strlen(line->buffer))
		tputs(data->save, 1, mini_putchar);
	tputs(data->del, 1, mini_putchar);
	//ft_putstr_fd("minishelldee> ", 1);
	write(1, line->buffer, ft_strlen(line->buffer));
	if (line->cursor < ft_strlen(line->buffer))
	{
		tputs(data->restore, 1, mini_putchar);
		if (command[0] != 0x7f)
			tputs(data->right, 1, mini_putchar);
	}
}

static int	ft_edit(t_data *data, t_line *line, char *command)
{
	char *tmp;

	if (command[0] == 0x7f)
	{
		tmp = line->buffer;
		line->buffer = ft_delete(line->buffer, line->cursor);
		line->cursor--;
		tputs(data->left, 1, mini_putchar);
		free(tmp);
	}
	else if (command[0] == '\n' || (command[0] == 4 && !line->cursor))
	{
		if (command[0] == '\n')
			write(1, "\n", 1);
		return (0);
	}
	else
	{
		tmp = line->buffer;
		line->buffer = ft_add(line->buffer, line->cursor, command);
		line->cursor++;
		free(tmp);
	}
	return (1);
}

static void	init_getline(t_line *line)
{
	line->cursor = 0;
	line->buffer = ft_strdup("");
	line->old_buff = NULL;
	line->reset = 0;
	ft_putstr_fd("minishell> ", 2);
}

char		*ft_getline(t_data *data)
{
	t_line	line;
	char	command[16];
	size_t	i;

	i = 1;
	init_getline(&line);
	while (1)
	{
		i = read(0, command, 16);
		if (i <= 0)
			break ;
		command[i] = 0;
		if (i > 1)
		{
			ft_line(data, &line, command);
			continue ;
		}
		if ((ft_strlen(line.buffer) == 0 && command[0] == 0x7f)
			|| (command[0] == 4 && line.cursor))
			continue ;
		else if (!ft_edit(data, &line, command))
			break ;
		print_frame(data, &line, command);
	}
	return (reset_line(data, line));
}