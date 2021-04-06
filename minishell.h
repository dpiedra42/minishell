/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:33:10 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/06 17:01:10 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <curses.h>
# include <termios.h>
# include <stdint.h>
# include <sys/ioctl.h>

# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include "libft/libft.h"

typedef struct	s_data
{
	char		*pwd;
	char		**env;
	int			fd_in;
	int			fd_out;
	int			redir;
}				t_data;

int				g_status;
char			*g_user_input;
int				g_quit;

void			ft_signal(void);
void			signal_exec(void);

int				ft_parse(char *input, t_data *data);
char			*clean_command(char *command);
void			copy_command(char *new_com, char *command);
void			copy_quote(char **command, char **new_com, char quote);

void			ft_escape(int *i, char *str);
void			quote_len(char **command, int *i, char quote);
void			escape_input(char **new_com, char **command);

void			find_variable(char **command, int *i, t_data *data);

int				ft_redir(char **command, t_data *data);
void			redir_quotes(char *str, int *i, char quote);
void			choose_redir(char **com, int i, t_data *data);
void			redir_into(char *str, int i, char **com, t_data *data);
void			redir_append(char *str, int i, char **com, t_data *data);
void			redir_from(char *str, int i, char **com, t_data *data);
char			*get_file(char *str, int *j);
void			delete_redir(char **com, int i, int j);
void			copy_file(char *src, char *dst, int i, int k);
int				filename_len(char *str);

int				parse_error(char *command);
void			skip_quotes(char *command, int *i);
int				redir_error(char *com, int *i, char c);

int				parser_filter(char *command, t_data *data, int pipe);
int				special_chars(char **command, int *i, t_data *data);

char			**split_command(char *command);
char			*new_str(char *command);
void			copy_split(char *command, char *new_com, char quote);

int				command_directory(char *command, t_data *data, int pipe);
void			pipe_exit(t_data *data);
void			close_fd(t_data *data);
void			free_inputs(char **inputs);
void			choose_builtin(char **inputs, t_data *data);

#endif