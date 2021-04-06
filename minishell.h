/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2021/01/11 12:03:49 by tpons             #+#    #+#             */
/*   Updated: 2021/02/05 16:26:37 by gsmets           ###   ########.fr       */
=======
/*   Created: 2021/01/30 14:33:10 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/06 18:13:12 by dpiedra          ###   ########.fr       */
>>>>>>> 82c3ec7ad2767275e90ec1f5e3f2346c91b2e109
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

<<<<<<< HEAD
int				envlen(char **env);
=======
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
int				change_dir(t_data *data, char *str);
void			ft_pwd(t_data *data);

void			ft_echo(char **inputs);
void			ft_env(char **env);
char			**copy_env(char **env);
int				e_len(char **env);
>>>>>>> 82c3ec7ad2767275e90ec1f5e3f2346c91b2e109
void			free_env(char **env);
char			**dup_env(char **env);
void			close_fds(t_data *data);

int				parser_start(char *str, t_data *data);
void			quote_len(char **str, int *i, char quote);
char			**input_split(char *str);

int				handle_basic(char *clean_input, t_data *data, int piped);
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
int				parser_delegator(char *input, t_data *data, int piped);
int				parser_error(char *str);
void			parser_variable(char **input_address, int *i, t_data *data);
int				parser_redir(char **input_address, t_data *data);
void			should_escape(int *i, char *str);
void			handle_redir(char **input_address, int i, t_data *data);
void			remove_redir_input(char **input_address, int i, int j);
int				get_name_len(char *str);
char			*get_filename(char *str, int *j);
void			input_copy(char *dst, char *src);
char			*input_cleaner(char *str);
void			copy_newsplit(char *src, char *dst, char quote);
void			escape_char(char **dst, char **src);

void			sig_exec_init(void);
void			sig_init(void);

void			error_sentence(char *str, int status);
void			handle_exit(char **inputs, t_data *data);

#endif
