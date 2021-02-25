/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:33:10 by dpiedra           #+#    #+#             */
/*   Updated: 2021/02/25 13:14:03 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <curses.h>
# include <termios.h>
# include <stdint.h>
# include <sys/ioctl.h>

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include "./libft/libft.h"

typedef struct  s_parse
{
				int len;
				int	num_commands;
				int h;
				int i;
}               t_parse;

int				g_status;
char			*g_user_input;
int				g_quit;

void			minishell();
void			ft_sigiq(int sig);
void			ft_signal(void);
int     		ft_parse(char *command);
char			*ft_clean_command(char *command);
void			quote_len(char **command, int *i, char quote);
void			copy_command(char *comline, char *command);
void			copy_inside_quotes(char **command, char **comline, char quote);
int				filter_command(char *command);
int				special_chars(char **command, int *i);
int				command_directory(char *command);
char			**split_command(char *str);
char			*new_str(char *src);
void			copy_newsplit(char *src, char *dst, char quote);
void			choose_builtin(char **inputs);
void			ft_echo(char **inputs);


#endif