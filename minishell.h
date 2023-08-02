/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:12:19 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/01 16:57:04 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <limits.h>

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
}	t_var;

typedef struct minishell
{
	char				*data;
	char				*exp;
	int					q;
	struct minishell	*link;
}	t_msh;

typedef struct env{
	char				*var;
	char				*value;
	struct env			*link;
}	t_env;

typedef struct exec
{
	char		**cmd;
	int			quo;
	int			in_fd;
	int			out_fd;
	int			p_aft;
	struct exec	*prev;
	struct exec	*link;
}	t_exec;

typedef struct release
{
	void			*ptr;
	struct release	*link;
}	t_free;

typedef struct global
{
	t_free	*f;
	t_msh	*msh;
	t_env	*env;
	char	pwd[PATH_MAX];
}t_gl;

extern t_gl	g_gl;

int		ft_isalpha(int c);
int		ft_isalnum(char c);
void	ft_expand(void);
int		ft_memcmp(char *p1, char *p2, int s);
int		check_syntax(char *s);
char	**ft_split(char *s);
char	*ft_strchr(const char *str, int c);
void	*ft_memcpy(void *dest, const void *src, int n);
void	release(char **tab);
int		doubles(char *s);
int		ft_strlen(char *s);
char	*ft_substr(char *s, int first, int len);
char	*ft_strjoin(char *s1, char *s2);
int		check_others(char *s, int i);
char	*get_type(char *s, int n, char *str);
char	*expanded_s(char *s, t_var *p);
char	*env_search(char *s, int pos, int pos1);
void	ft_ignore(void);
char	*dollars(char *s, t_var *p);
void	ft_putstr(char *s, int fd);
void	ft_error(char *s);
void	alloc_list(void *line);
void	ft_alloc(void *p);
void	new_init(t_exec *x);
char	*special_ch(char *s);
char	*expand_hd(char *s);
char	*name_heredoc(void);
char	*ft_itoa(int n);
char	*ft_strdup(char *src);
void	ft_alloc_tab(char **tab);
void	free_list(void);
t_exec	*exec_list(t_exec *x, t_exec *tmp, t_exec *new);

void	ft_builtins(t_exec *x);

#endif