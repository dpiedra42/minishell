/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:34:18 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/13 17:44:02 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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