/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:33:10 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/15 19:06:22 by dpiedra          ###   ########.fr       */
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
}               t_parse;

void    minishell();
// void    ft_sigint(int sig);
void    ft_signal(void);
int     ft_parse(char *command);
char	*ft_clean_command(char *command);
int		find_len(char *command);
void	quote_len(char **command, int *i, char quote);
void	copy_command(char *comline, char *command);
void	copy_inside_quotes(char **command, char **comline, char quote);
// int     count_commands(char *command, char *sep);
// int	    count_chars(char *command, char *sep);
// char	*ft_makestr(int size);

#endif