/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:19:01 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/10 19:21:09 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**filter_commands(char **commands)
{
	char	**fil_coms;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (commands[i])
	{
		if(commands[i][j] == ' ' && commands[i][j])
			j++;
		if(commands[i][j] == '"' || '\'')
			ft_quotes();
		
	}
	return (fil_coms);
}

char	*ft_makestr(int size)
{
	char	*str;
	int	i;

	i = 0;
	if (!(str = malloc(sizeof(char) * (size + 1))))
		exit(EXIT_FAILURE);
	ft_memset((char*)str, (int)'\0', size + 1);
	return (str);
}

int	count_chars(char *command, char *sep)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (command[len])
	{
		if (command[len] == '"' || command[len] == '\'')
		{
			len++;
			while (command[len] != '"' || command[len] == '\'')
				len++;
		}
		if (command[len] == sep[i] && command[len + 1] != sep[i] &&
			command[len - 1] != sep[i])
			return (len);
		len++;
	}
	return (len);
}

int	count_commands(char *command, char *sep)
{
	int i;
	int number;

	number = 0;
	i = 0;
	while (*command)
	{
		if (*command == '"' || *command == '\'')
		{
			command++;
			while (*command != '"' || *command == '\'')
				command++;
		}
		if (*command == sep[i] && *(command + 1) != sep[i] &&
			*(command - 1) != sep[i])
			number++;
		command++;
	}
	return (number + 1);
}