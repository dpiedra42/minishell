/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:10:26 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/26 19:22:29 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
static char	*copy_args(char *dst, char *src)
{
	int len;
	int i;

	printf("src = %s\n", src);
	printf("dst= %s\n", dst);
	len = ft_strlen(src);
	i = 0;
	dst = malloc(sizeof(char) * len + 1);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	ft_echo(t_data *data, char **args)
=======
void	ft_echo(char **args)
>>>>>>> 876a007cb1236719a6933565e05e09feaea5f862
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	g_status = 0;
<<<<<<< HEAD
	data->echo = NULL;
	while (args[i] && !ft_strcmp(args[i], "-n") && i++)
		flag = 1;
	if (flag == 1 && args[i])
		data->echo = copy_args(data->echo, args[i]);
	printf("echo = %s\n", data->echo);
=======
	g_echo = ft_strdup("\0");
	while (args[i] && !ft_strcmp(args[i], "-n") && i++)
		flag = 1;
	if (flag == 1)
		g_echo = ft_strdup(args[i]);
>>>>>>> 876a007cb1236719a6933565e05e09feaea5f862
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
