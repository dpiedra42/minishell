/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_escape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:13:23 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/16 17:23:04 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	escape_input(char **comline, char **command)
{
	char q;

	(*command)++;
	if (**command == '\'')
		q = '"';
	else
		q = '\'';
	*((*comline)++) = q;
	*((*comline)++) = *((*command)++);
	*((*comline)++) = q;
}

void	ft_escape(int *i, char *str)
{
	if (str[(*i)] == '\\')
		(*i)++;
}
