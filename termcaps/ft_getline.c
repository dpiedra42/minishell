/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:01:40 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/13 19:15:57 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_loop_history(t_data *data, int key, int *cur)
{
	

}

int			ft_arrow(char *command)
{
	command += 2;
	if (*command == 'A' || *command == 'B')
		return (*command - 65);
	return (-1);
}

void		ft_line(t_data *data, char *command)
{
	static int	current = -1;
	int			key;

	if (data->reset)
	{
		current = -1;
		return ;
	}
	key = ft_arrow(command);
	if (key == 0 || key == 1)
		ft_loop_history(data, key, &current);
}

char		*ft_getline(t_data *data)
{
	char	command[16];
	size_t	i;

	i = 1;
	while (1)
	{
		i = read(0, command, 16);
		if (i <= 0)
			break ;
		command[i] = 0;
		if (i > 1)
		{
			ft_line(data, command);
			continue ;
		}

	}
}