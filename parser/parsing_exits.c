/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:27:59 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/05 16:46:02 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_escape(int *i, char *str)
{
	if (str[(*i)] == '\\')
		(*i)++;
}

void	exit_pipe(t_data *data)
{
	free_inputs(data->env);
	if (g_user_input)
		free(g_user_input);
	free(data->pwd);
	exit(EXIT_SUCCESS);
}

void	close_fd(t_data *data)
{
	if (data->fd_in != 0)
	{
		close(data->fd_in);
		data->fd_in = 0;
	}
	if (data->fd_out != 1)
	{
		close(data->fd_out);
		data->fd_out = 1;
	}
}

void	free_inputs(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		free(inputs[i]);
		i++;
	}
	free(inputs);
}
