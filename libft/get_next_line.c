/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 15:28:52 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/05 14:56:04 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strappend(char *str, char c)
{
	int		len;
	char	*new;
	int		i;

	len = ft_strlen(str);
	i = 0;
	new = malloc((len + 2) * sizeof(char));
	if (!new)
		exit(EXIT_FAILURE);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	return (new);
}

int		get_next_line(int fd, char **line)
{
	char	buf;
	char	*str;
	char	*tmp;
	int		ret;

	buf = 0;
	str = malloc(sizeof(char));
	if (!str)
		exit(EXIT_FAILURE);
	*str = '\0';
	while ((ret = read(fd, &buf, 1)) && buf != '\n')
	{
		tmp = ft_strappend(str, buf);
		free(str);
		str = tmp;
	}
	*line = str;
	if (ret)
		return (1);
	else
		return (0);
}
