/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:34:18 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/15 16:15:29 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*reset_line(t_data *data, t_line line)
{
	line.reset = 1;
	ft_line(data, &line, NULL);
	free(line.old_buff);
	return(line.buffer);
}

int		test_check(int test, int *a, int *b)
{
	if (test)
		return (a);
	else
		return (b);
}

int		max_int(int a, int b)
{
	return (test_check(a > b, a, b));
}

int	mini_putchar(int c)
{
	write(1, &c, 1);
	return (c);
}

int	reset_terminal(struct termios *backup, t_data *data)
{
	tputs(data->reset, 1, mini_putchar);
	return (!tcsetattr(STDIN_FILENO, TCSANOW, backup));
}