/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:19:01 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/05 15:15:39 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_makestr(int size)
{
	char	*str;
	int	i;

	i = 0;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ft_memset((char*)str, (int)'\0', size + 1);
	return (str);
}

int	count_chars(char *command, char *sep)
{
	int i;
	int len;

	len = 0;
	while (command[len])
	{
		i = 0;
		while (sep[i])
		{
			if (command[len] == sep[i] && command[len + 1] != sep[i] &&
				command[len - 1] != sep[i])
				return (len);
			i++;
		}
		len++;
	}
	return (len);
}

int	count_commands(char *command, char *sep)
{
	int i;
	int number;

	number = 0;
	while (*command)
	{
		i = 0;
		while (sep[i])
		{
			if (*command == sep[i] && *(command + 1) != sep[i] &&
				*(command - 1) != sep[i])
				number++;
			i++;
		}
		command++;
	}
	return (number + 1);
}