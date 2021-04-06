/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:33:10 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/06 15:28:54 by dpiedra          ###   ########.fr       */
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


// int				envlen(char **env);
// void			free_env(char **env);
// char			**dup_env(char **env);
// void			close_fds(t_data *data);

// int				parser_start(char *str, t_data *data);
// void			quote_len(char **str, int *i, char quote);
// char			**input_split(char *str);

// int				handle_basic(char *clean_input, t_data *data, int piped);
// void			handle_echo(char **args);
// void			handle_cd(char **args, t_data *data);
// void			handle_unset(char **inputs, t_data *data);

// char			**export_env(char **old_env, char *export);
// void			handle_env(char **env);

// int				change_pwd(t_data *data, char *input);
// void			handle_pwd(t_data *data);

// int				is_relative(char *str);
// char			**gen_paths(int index, t_data *data, char *input);
// int				check_exec(char **inputs, t_data *data);
// void			handle_exec(char **args, t_data *data);

// void			replace_var(char *new_var, t_data *data, int index);
// int				var_index(char *name, t_data *data);
// int				print_export(char **env);
// int				check_export(char *str);
// char			**copy_export_env(char **env);
// void			handle_export(char **args, t_data *data);

// int				handle_pipe(char *input1, char *input2, t_data *data);
// int				parser_delegator(char *input, t_data *data, int piped);
// int				parser_error(char *str);
// void			parser_variable(char **input_address, int *i, t_data *data);
// int				parser_redir(char **input_address, t_data *data);
// void			should_escape(int *i, char *str);
// void			handle_redir(char **input_address, int i, t_data *data);
// void			remove_redir_input(char **input_address, int i, int j);
// int				get_name_len(char *str);
// char			*get_filename(char *str, int *j);
// void			input_copy(char *dst, char *src);
// char			*input_cleaner(char *str);
// void			copy_newsplit(char *src, char *dst, char quote);
// void			escape_char(char **dst, char **src);

// void			sig_exec_init(void);
// void			sig_init(void);

// void			error_sentence(char *str, int status);
// void			handle_exit(char **inputs, t_data *data);

void			ft_signal(void);
void			signal_exec(void);

int				ft_parse(char *command, t_data *data);
char			*clean_command(char *command);
void			copy_command(char *new_com, char *command);
int				parser_filter(char *command, t_data *data, int pipe);

void			quote_len(char **command, int *i, char quote);
void			escape_input(char **new_com, char **command);
int				command_directory(char *command, t_data *data, int pipe);
void			choose_builtin(char **inputs, t_data *data);

void			find_variable(char **command, int *i, t_data *data);
int				special_chars(char **command, int *i, t_data *data);

int				parse_error(char *command);
void			skip_quotes(char *command, int *i);
int				redir_error(char *command, int *i, char redir);

int				ft_redir(char **com, t_data *data);
void			redir_quotes(char *str, int *i, char quote);
void			choose_redir(char **com, int i, t_data *data);
void			redir_into(char *str, int i, char **com, t_data *data);
void			redir_from(char *str, int i, char **com, t_data *data);

void			redir_append(char *str, int i, char **com, t_data *data);
char			*get_file(char *str, int *j);
void			del_redir(char **com, int i, int j);
void			copy_file(char *src, char *dst, int i, int k);

void			ft_escape(int *i, char *str);
void			free_inputs(char **inputs);
void			close_fd(t_data *data);
void			exit_pipe(t_data *data);

char			**split_command(char *command);
char			*new_str(char *commands);
void			copy_split(char *command, char *new_com, char quote);

void			ft_echo(char **inputs);
void			ft_pwd(t_data *data);

void			ft_cd(char **input, t_data *data);
void			ft_error(char *str, int status);
int				cd_empty(t_data *data);
int				cd_minus(t_data *data);
int				cd_path(char **input, t_data *data);

int				env_index(char *id, t_data *data);
int				change_dir(t_data *data, char *str);
void			set_oldpwd(t_data *data);
void			new_pwd(t_data *data);

int				env_len(char **env);
char			**get_env(char **env);
void			replace_var(char *new_pwd, t_data *data, int index);
void			ft_env(char **env);

void			ft_exit(char **inputs, t_data *data);
int				check_num(char *str);

char			**exp_env(char **env, char *exp);
void			ft_export(char **inputs, t_data *data);
int				check_exp(char *input);
int				put_exp(char **env);
void			export_a(t_data *data);

void			ft_unset(char **inputs, t_data *data);
char			**unset_env(char **env, int id);

int				ft_pipe(char *command, char *new_com, t_data *data);
void			ft_parent(char *new_com, t_data *data, int pid, int *fds);

int				check_exec(char **inputs, t_data *data);
int				check_path(char **inputs, t_data *data);
void			free_env(char **env);

char			**make_paths(int id, t_data *data, char *input);
int				exec_2(char **inputs, t_data *data);
int				exec(char **inputs, t_data *data);
void			ft_exec(char **inputs, t_data *data);

#endif