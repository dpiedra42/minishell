/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:34:18 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/23 16:19:00 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*restart_line(t_data *data, t_line line)
{
	line.reset = 1;
	ft_line(data, &line, NULL);
	free(line.old_com);
	return (line.com);
}

void	*test_check(int test, void *a, void *b)
{
	if (test)
		return (a);
	else
		return (b);
}

int		max_int(int a, int b)
{
	return (ul_testcheck(a > b, a, b));
}

int		mini_putchar(int c)
{
	write(1, &c, 1);
	return (c);
}

int		reset_terminal(void)
{
	struct termios tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_cflag |= (ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &tattr);
	return (1);
}
