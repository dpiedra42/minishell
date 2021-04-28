/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:10:26 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/28 15:37:23 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_args(char *src)
{
	char	*dst;
	int		len;
	int		i;

	len = ft_strlen(src);
	i = 0;
	if (!(dst = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	ft_echo(t_data *data, char **args)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	g_status = 0;
	while (args[i] && !ft_strcmp(args[i], "-n") && i++)
		flag = 1;
	if (flag == 1 && args[i])
		data->echo = copy_args(args[i]);
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		ft_putstr("\n");
}
