/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:35:31 by gsmets            #+#    #+#             */
/*   Updated: 2021/04/02 17:10:32 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(char *str, int fd)
{
	int count;

	if (str == NULL)
		return ;
	count = 0;
	while (str[count])
		count++;
	write(fd, str, count);
	write(fd, "\n", 1);
}
