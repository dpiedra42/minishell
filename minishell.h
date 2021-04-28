/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:03:49 by tpons             #+#    #+#             */
/*   Updated: 2021/04/28 14:50:26 by dpiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <termcap.h>
# include <curses.h>
# include <termios.h>
# include <stdint.h>
# include <sys/ioctl.h>

# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include "libft/libft.h"

# define HISTORY_SIZE 1000
# define HISTORY_FILE ".minishell_history"

typedef struct	s_line
{
	size_t		length;
	char		*com;
	char		*old_com;
	int			reset;
}				t_line;

typedef	struct	s_data
{
	char		**env;
	int			fd_in;
	int			fd_out;
	char		*pwd;
	int			redir;
	char		*reset;
	char		*del;
	char		*left;
	char		*right;
	char		*restore;
	char		*save;
	char		*echo;
}				t_data;

int				g_status;
char			*g_history[HISTORY_SIZE];
int				g_last;
char			*g_user_input;
int				g_quit;

int				main(int ac, char **av, char **env);
void			init_data(t_data *data, char **env);
void			minishell(t_data *data);
void			ft_eof(t_data *data, char *user_input);

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

void			ft_echo(t_data *data, char **args);
char			*copy_args(char *src);
void			ft_pwd(t_data *data);
void			ft_env(char **env);

void			ft_cd(char **args, t_data *data);
int				cd_empty(t_data *data);
int				reg_cd(char **inputs, t_data *data);
int				change_dir(t_data *data, char *input);
void			set_oldpwd(t_data *data);
void			new_pwd(t_data *data);

char			**copy_env(char **env);
int				e_len(char **env);
void			free_env(char **env);

void			ft_error(char *error, int status);
void			ft_exit(char **inputs, t_data *data);
int				check_num(char *str);

void			ft_export(char **args, t_data *data);
void			reg_export(t_data *data);
char			**exp_env(char **env, char *exp);
void			replace_var(char *var, t_data *data, int id);
int				env_index(char *name, t_data *data);
int				put_exp(char **env);
int				check_exp(char *str);

void			ft_unset(char **inputs, t_data *data);
char			**unset_env(char **env, int id);

void			ft_exec(char **args, t_data *data);
int				check_exec(char **inputs, t_data *data);
int				check_path(char **inputs, t_data *data);
char			**make_paths(int index, t_data *data, char *input);
int				exec(char **inputs, t_data *data);
int				exec_2(char **inputs, t_data *data);

int				ft_pipe(char *input1, char *input2, t_data *data);
void			ft_parent(char *new_com, t_data *data, int pid, int *fds);

void			signal_exec(void);
void			ft_signal(void);

void			get_history(void);
void			add_command(char *command);
void			write_history(void);

int				reset_terminal(struct termios *backup, t_data *data);
int				mini_putchar(int c);
int				max_int(int a, int b);
void			*test_check(int test, void *a, void *b);
char			*restart_line(t_data *data, t_line line);

char			*ft_getline(t_data *data, int *red);

void			ft_line(t_data *data, t_line *line, char *command);
int				ft_arrow(char *command);
char			*ft_delete(char *str, int i);
char			*ft_add(char *str, int i, char *c);

unsigned long	ul_testcheck(int test, unsigned long a, unsigned long b);
void			check_status(t_line *line);

#endif
