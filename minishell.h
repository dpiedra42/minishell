/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:33:10 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/10 17:46:11 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include "./libft/libft.h"

typedef struct  s_parse
{
                int len;
                int	num_commands;
                int h;
                int i;
                int j;
}               t_parse;

void    minishell();
// void    ft_sigint(int sig);
void    ft_signal(void);
void    ft_parse(char *command);
char	**ft_create_commands(char *command, char *sep);
int     count_commands(char *command, char *sep);
int	    count_chars(char *command, char *sep);
char	*ft_makestr(int size);
char	**filter_commands(char **commands);

#endif