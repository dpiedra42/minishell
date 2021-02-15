/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:26:40 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/12 18:16:18 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*clean_quotes(char *str)
// {
// 	char	*new_str;
// 	int		i;

// 	i = ft_strlen(str);
// 	if (!(new_str = malloc(sizeof(char) * (i + 1))))
// 		return (NULL);
// 	while (*str != '"' && *str)
// 		*(new_str++) = *(str++);
// 	if (*str == '"')
// 	{
// 		copy_quote(&str, &new_str);
// 	}
// 	*new_str = '\0';
// 	return (new_str);
// }
