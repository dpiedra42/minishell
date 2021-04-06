/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:33:10 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/06 18:26:24 by dpiedra          ###   ########.fr       */
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

void			ft_escape(int *i, char *str);
void			quote_len(char **command, int *i, char quote);
void			escape_input(char **new_com, char **command);

void			find_variable(char **command, int *i, t_data *data);

int				ft_redir(char **command, t_data *data);
void			choose_redir(char **com, int i, t_data *data);
char			*get_file(char *str, int *j);
void			delete_redir(char **com, int i, int j);
int				filename_len(char *str);

int				parse_error(char *command);

int				parser_filter(char *command, t_data *data, int pipe);

char			**split_command(char *command);
void			copy_split(char *command, char *new_com, char quote);

int				command_directory(char *command, t_data *data, int pipe);
void			close_fd(t_data *data);

void			ft_cd(char **input, t_data *data);

void			ft_echo(char **inputs);
void			ft_env(char **env);
char			**copy_env(char **env);
int				e_len(char **env);
void			free_env(char **env);
int				env_index(char *id, t_data *data);

void			ft_exec(char **inputs, t_data *data);
int				check_exec(char **inputs, t_data *data);

void			ft_exit(char **inputs, t_data *data);
void			ft_error(char *str, int status);

void			ft_export(char **inputs, t_data *data);
char			**exp_env(char **env, char *exp);
void			replace_var(char *new_var, t_data *data, int id);
int				put_exp(char **env);
int				check_exp(char *str);

int				ft_pipe(char *command, char *new_com, t_data *data);
void			ft_unset(char **inputs, t_data *data);

#endif