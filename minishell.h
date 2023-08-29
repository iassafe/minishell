/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:12:19 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/19 16:32:39 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct variables{
	int		dq;
	int		sq;
	int		ch;
	int		n;
	char	chr;
	int		i;
	int		j;
	char	*var;
	char	*var1;
	char	*value;
	char	*s1;
	char	*s2;
	char	*s3;
	int		pos;
	int		pos1;
	int		d;
	char	*line;
	char	**tab;
	char	**env;
	int		pipe_end[2];
}	t_var;

typedef struct minishell
{
	char				*data;
	char				*exp;
	int					q_del;
	int					*pos_i;
	int					ch_val;
	struct minishell	*link;
}	t_msh;

typedef struct env{
	char				*var;
	char				*value;
	struct env			*link;
	struct env			*prev;
}	t_env;

typedef struct exec
{
	char		**cmd;
	int			in_fd;
	int			out_fd;
	pid_t		pid;
	int			ch_val;
	struct exec	*prev;
	struct exec	*link;
}	t_exec;

typedef struct release
{
	void			*ptr;
	struct release	*link;
}	t_free;

typedef struct release_env
{
	void				*ptr;
	struct release_env	*link;
}	t_free_env;

typedef struct global
{
	t_free		*f;
	t_free_env	*f_env;
	t_msh		*msh;
	t_env		*env;
	t_exec		*xec;
	char		pwd[PATH_MAX];
	int			em_e;
	int			exit;
	int			ctrl_c;
}t_gl;

extern t_gl	g_gl;

// syntax error
int		doubles(char *s);
int		check_syntax(char *s);
int		check_others(char *s, int i);
char	*get_type(char *s, int n, char *str);

// env
char	*ft_itoa1(int n);
size_t	ft_nb_len(int nb);
void	ft_alloc_env(void *p);
void	alloc_list_env(void *line);
void	free_list_env(void);
void	ft_create_node(t_env *new);
char	*ft_substr1(char *s, int first, int len);
char	*ft_strjoin1(char *s1, char *s2);

// expanding
void	ft_expand(void);
void	ft_ignore(void);
void	no_expanded(void);
char	*special_ch(t_msh *x, char *s, int *pos_i);
char	*dollars(char *s, t_var *p);
char	*expanded_s(t_msh *x, char *s, t_var *p, int *pos_i);
char	*env_search(t_msh *x, char *s, int pos, int *pos_i);
void	list_env(char **env, t_env *next, t_env	*new);
int		*check_var_form(char *s, t_var *p);
char	*join_value(char *s, int pos1, t_env *c_env, t_msh *x);
void	check_value(t_msh *x, char *value);

// open file
void	new_init(t_exec *x);
char	*expand_hd(char *s);
char	*name_heredoc(void);
char	*wr_herdoc(char *line, int in_fd, int fd);
t_exec	*exec_list(t_exec *x, t_exec *tmp, t_exec *new);

// free
void	free_list(void);
void	ft_alloc(void *p);
void	release(char **tab);
void	alloc_list(void *line);
void	ft_alloc_tab(char **tab);

// libft
char	*ft_itoa(int n);
int		ft_isdigit(int c);
void	ft_error(char *s);
int		ft_isalpha(int c);
int		ft_strlen(char *s);
int		ft_atoi(const char *str);
int		ft_isalnum(char c);
char	**ft_split(char *s);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putstr(char *s, int fd);
int		ft_memcmp(char *p1, char *p2, int s);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char *s, int first, int len);
void	*ft_memcpy(void *dest, const void *src, int n);

// bultins
void	xec_cd(t_exec *x);
void	cd_with(char *cmd);
void	xec_env(t_exec *x);
void	check_arg(t_exec *x);
void	xec_unset(t_exec *x);
void	ft_builtins(t_exec *x);
void	check_export(t_exec *x);
int		check_builtins(char	*cmd);
void	xec_echo(t_exec *x, t_var *v);

// 	execution
char	**copy_env(void);
char	**get_paths(void);
void	ft_execution(void);
int		check_slash(char *cmd);
void	execute(t_exec *next);
void	close_fd(t_exec *head);
void	open_pipe(t_exec *next);
int		check_dir(char *cmd);
char	**fun_split(char *s, char c);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
void	searching_path(t_exec *next, char **paths_tab);

// signals
void	ctrl_d(void);
void	sig_herdoc(int signum);
void	sigint_handler(int si);
void	signals_handler(int status);
void	quit_herdoc(char *line, int fd);

#endif