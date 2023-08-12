/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:12:19 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/12 14:42:31 by iassafe          ###   ########.fr       */
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
	int		egal;

	char	**paths_tab;
	pid_t	pid;
	int		status;
	int		pipe_end[2];
}	t_var;

typedef struct minishell
{
	char				*data;
	char				*exp;
	int					q_del;
	int					q_empty;
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
	int			quo;
	int			in_fd;
	int			out_fd;
	int			p_aft;
	pid_t		pid;
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
void	free_list_env(void);
void	ft_alloc_env(void *p);
void	alloc_list_env(void *line);
void	ft_create_node(t_env *new);
char	*ft_substr1(char *s, int first, int len);

// expand
void	ft_expand(void);
void	ft_ignore(void);
char	*special_ch(char *s);
char	*dollars(char *s, t_var *p);
char	*expanded_s(char *s, t_var *p);
char	*env_search(char *s, int pos, int pos1);

// open file
void	new_init(t_exec *x);
char	*expand_hd(char *s);
char	*name_heredoc(void);
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
int		ft_isalnum(char c);
char	**ft_split(char *s);
char	*ft_strdup(char *src);
int		ft_atoi(const char *str);
void	ft_putstr(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *str, int c);
int		ft_memcmp(char *p1, char *p2, int s);
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
void	xec_echo(t_exec *x, t_var *v);

// 	execution
void	xec_cmd(void);
char	**fun_split(char *s, char c);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
#endif