/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:03:49 by tpons             #+#    #+#             */
/*   Updated: 2021/04/07 15:54:50 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <curses.h>
# include <termios.h>
# include <stdint.h>
# include <sys/ioctl.h>

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include "libft/libft.h"

typedef	struct	s_data
{
	char		**env;
	int			fd_in;
	int			fd_out;
	char		*pwd;
	int			redir;
}				t_data;

int				g_status;
char			*g_user_input;
int				g_quit;

int				ft_parse(char *str, t_data *data);
char			*clean_command(char *str);
void			copy_command(char *dst, char *src);
void			copy_quote(char **src, char **dst, char quote);

void			ft_escape(int *i, char *str);
void			escape_input(char **dst, char **src);
void			quote_len(char **str, int *i, char quote);

int				parsing_filter(char *input, t_data *data, int piped);
void			find_variable(char **command, int *i, t_data *data);
int				special_chars(char **input, int *i, t_data *data);

int				command_directory(char *clean_input, t_data *data, int piped);
void			pipe_exit(t_data *data);
void			close_fd(t_data *data);
void			free_inputs(char **inputs);
void			choose_builtin(char **inputs, t_data *data);

int				parsing_error(char *str);
void			skip_quotes(char *str, int *i);
int				redir_error(char *str, int *i, char c);

int				ft_redir(char **input_address, t_data *data);
void			redir_quotes(char *str, int *i, char quote);
void			choose_redir(char **input_address, int i, t_data *data);
void			redir_into(char *str, int i, char **input, t_data *data);
void			redir_append(char *str, int i, char **input, t_data *data);

void			redir_from(char *str, int i, char **input, t_data *data);
void			remove_redir(char **input, int i, int j);
char			*get_file(char *str, int *j);
int				get_file_len(char *str);
void			make_file(char *str, char *file, int i, int k);

char			**split_command(char *str);
char			*new_strs(char *command);
void			copy_split(char *command, char *new_str, char quote);

int				envlen(char **env);
void			free_env(char **env);
char			**dup_env(char **env);

void			handle_echo(char **args);
void			handle_cd(char **args, t_data *data);
void			handle_unset(char **inputs, t_data *data);

char			**export_env(char **old_env, char *export);
void			handle_env(char **env);

int				change_pwd(t_data *data, char *input);
void			handle_pwd(t_data *data);

int				is_relative(char *str);
char			**gen_paths(int index, t_data *data, char *input);
int				check_exec(char **inputs, t_data *data);
void			handle_exec(char **args, t_data *data);

void			replace_var(char *new_var, t_data *data, int index);
int				var_index(char *name, t_data *data);
int				print_export(char **env);
int				check_export(char *str);
char			**copy_export_env(char **env);
void			handle_export(char **args, t_data *data);

int				handle_pipe(char *input1, char *input2, t_data *data);
void			copy_newsplit(char *src, char *dst, char quote);

void			sig_exec_init(void);
void			sig_init(void);

void			error_sentence(char *str, int status);
void			handle_exit(char **inputs, t_data *data);

#endif
