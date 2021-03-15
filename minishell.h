/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:33:10 by dpiedra           #+#    #+#             */
/*   Updated: 2021/03/15 18:02:54 by dpiedra          ###   ########.fr       */
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
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include "./libft/libft.h"

typedef struct	s_data
{
	char	*pwd;
	char	**env;
	int		fd_in;
	int		fd_out;
	int		redir;
}				t_data;

int				g_status;
char			*g_user_input;
int				g_quit;

void			ft_sigiq(int sig);
void			ft_signal(void);
int				ft_parse(char *command, t_data *data);
char			*ft_clean_command(char *command);
void			quote_len(char **command, int *i, char quote);
void			copy_command(char *comline, char *command);
void			escape_input(char **comline, char **command);
void			copy_inside_quotes(char **command, char **comline, char quote);
int				filter_command(char *command, t_data *data);
void			find_variable(char **command, int *i, t_data *data);
int				special_chars(char **command, int *i, t_data *data);
int				command_directory(char *command, t_data *data, int pipe);
char			**split_command(char *str);
char			*new_str(char *src);
void			copy_newsplit(char *src, char *dst, char quote);
void			choose_builtin(char **inputs, t_data *data);
void			ft_echo(char **inputs);
void			ft_pwd(t_data *data);
char			**get_env(char **env);
int				env_len(char **env);
void			ft_env(t_data *data);
int				env_index(t_data *data, char *id);
void			replace_var(char *new_pwd, t_data *data, int index);
void			ft_cd(char **input, t_data *data);
int				cd_empty(t_data *data);
void			ft_error(char *str, int status);
int				change_dir(t_data *data, char *str);
void			set_oldpwd(t_data *data);
void			new_pwd(t_data *data);
int				clean_quotes(char **com);
void			parsing_quotes(char *str, int *i, char quote);
void			close_fd(t_data *data);
void			free_inputs(char **inputs);
void			exit_pipe(t_data *data);
void			ft_parent(char *new_com, t_data *data, int pid, int *fds);
int				ft_pipe(char *command, char *new_com, t_data *data);
void			ft_exec(char **inputs, t_data *data);
int				exec(char **inputs, t_data *data);
int				exec_2(char **inputs, t_data *data);
char			**make_paths(int id, t_data *data, char *input);
int				check_exec(char **inputs, t_data *data);
int				check_exec_path(char **inputs, t_data *data);
void			signal_exec(void);
void			exec_sigiq(int sig);

#endif
