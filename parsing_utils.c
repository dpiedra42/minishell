/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:19:01 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/15 19:06:18 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_inside_quotes(char **command, char **comline, char quote)
{
	while (**command != quote)
	{
		*((*comline)++) = *((*command)++);
	}
}

void	copy_command(char *comline, char *command)
{
	char	quote;

	while (*command)
	{
		if (*command == ' ' && (*(command + 1) == ' ' || *(command + 1) == '\0'))
			command++;
		else if (*command == '"' || *command == '\'')
		{
			*(comline++) = *command;
			quote = *(command++);
			copy_inside_quotes(&command, &comline, quote);
			*(comline++) = *(command++);
		}
		else
			*(comline++) = *(command++);
	}

}

void	quote_len(char **command, int *i, char quote)
{
	while (**command != quote && **command)
	{
		(*i)++;
		(*command)++;
	}
}

int		find_len(char *command)
{
	int i;
	char quote;

	i = 0;
	while (*command)
	{
		if (*command == ' ' && (*(command + 1) == ' ' || *(command + 1) == '\0'))
			command++;
		else if (*command == '"' || *command == '\'')
		{
			quote = *(command++);
			quote_len(&command, &i, quote);
			if (!*command)
				return (-1);
			command++;
			i = i + 2;
		}
		else if (command++)
			i++;
	}
	return (i);
}

// char	*ft_makestr(int size)
// {
// 	char	*str;
// 	int	i;

// 	i = 0;
// 	if (!(str = malloc(sizeof(char) * (size + 1))))
// 		exit(EXIT_FAILURE);
// 	ft_memset((char*)str, (int)'\0', size + 1);
// 	return (str);
// }

// int	count_chars(char *command, char *sep)
// {
// 	int len;

// 	len = 0;
// 	while (command[len])
// 	{
// 		if (command[len] == '"' || command[len] == '\'')
// 		{
// 			len++;
// 			while (command[len] != '"' || command[len] == '\'')
// 				len++;
// 		}
// 		if (command[len] == *sep && command[len + 1] != *sep &&
// 			command[len - 1] != *sep)
// 			return (len);
// 		len++;
// 	}
// 	return (len);
// }

// int	count_commands(char *command, char *sep)
// {
// 	int number;

// 	number = 0;
// 	while (*command)
// 	{
// 		if (*command == '"' || *command == '\'')
// 		{
// 			command++;
// 			while ((*command != '"' || *command == '\'') && *command)
// 				command++;
// 			if (!*command)
// 				return (-1);
// 		}
// 		if (*command == *sep && *(command + 1) != *sep &&
// 			*(command - 1) != *sep)
// 			number++;
// 		command++;
// 	}
// 	return (number + 1);
// }