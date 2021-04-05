/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:33:10 by dpiedra           #+#    #+#             */
/*   Updated: 2021/04/05 16:44:00 by dpiedra          ###   ########.fr       */
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

void			ft_sigiq(int sig);
void			ft_signal(void);
void			signal_exec(void);
void			exec_sigiq(int sig);

int				ft_parse(char *command, t_data *data);
char			*clean_command(char *command);
void			copy_command(char *new_com, char *command);
int				parser_filter(char *command, t_data *data, int pipe);

void			quote_len(char **command, int *i, char quote);
void			copy_quote(char **command, char **new_com, char quote);
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
