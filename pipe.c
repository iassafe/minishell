/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:08:57 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/12 18:45:32 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(char	*cmd)
{
	if ((!ft_memcmp(cmd, "echo", 5))
		|| (!ft_memcmp(cmd, "pwd", 4))
		|| (!ft_memcmp(cmd, "env", 4))
		|| (!ft_memcmp(cmd, "export", 7))
		|| (!ft_memcmp(cmd, "unset", 6))
		|| (!ft_memcmp(cmd, "cd", 3))
		|| (!ft_memcmp(cmd, "exit", 4)))
		return (1);
	return (0);
}

char	**get_paths(void)
{
	t_env	*next;
	char	**paths_tab;
	t_var	p;

	p.i = 0;
	paths_tab = NULL;
	next = g_gl.env;
	while (next)
	{
		if (!ft_memcmp(next->var, "PATH", 5))
		{
			paths_tab = fun_split(next->value, ':');
			ft_alloc_tab(paths_tab);
			break ;
		}
		next = next->link;
	}
	return (paths_tab);
}

void	ft_dup(t_exec *next)
{
	t_exec	*head;

	head = g_gl.xec;
	if (next->out_fd != 1)
		dup2(next->out_fd, 1);
	if (next->in_fd != 0)
		dup2(next->in_fd, 0);
	while (head)
	{
		if (head->in_fd != 0)
			close(head->in_fd);
		if (head->out_fd != 1)
			close(head->out_fd);
		head = head->link;
	}
}

void	ft_child(t_exec *next, char *xec_path)
{

	next->pid = fork();
	if (next->pid < 0)
		exit (1);
	if (next->pid == 0)
	{
		ft_dup(next);
		execve(xec_path, next->cmd, NULL);
		exit(127);
	}
}

void	xec1cmd(t_exec *next, char *xec_path)
{
	t_var	p;

	if (next->link)
	{
		if (pipe(p.pipe_end) == -1)
		{
			perror("Pipe creation failed");
			exit(1);
		}
		if (next->out_fd == 1)
			next->out_fd = p.pipe_end[1];
		else
			close(next->out_fd);
		if (next->link->in_fd == 0)
			next->link->in_fd = p.pipe_end[0];
		else
			close(next->link->in_fd);
	}
	ft_child(next, xec_path);
}

void	execute(t_exec *next, char **paths_tab)
{
	t_var	p;
	char	*xec_path;

	p.i = 0;
	while (paths_tab[p.i])
	{
		if (next->cmd[0][0] == '\0')
		{
			ft_putstr (ft_strjoin3("minishell: ", next->cmd[0], \
			": command not found\n"), 2);
			return ;
		}
		xec_path = ft_strjoin3(paths_tab[p.i], "/", next->cmd[0]);
		if (xec_path && access(xec_path, X_OK) == 0)
		{
			xec1cmd(next, xec_path);
			return ;
		}
		p.i++;
	}
	if (!paths_tab[p.i])
		ft_putstr (ft_strjoin3("minishell: ", next->cmd[0], \
		": command not found\n"), 2);
}

void	xec_cmd(void)
{
	t_exec	*next;
	t_var	p;

	p.paths_tab = get_paths();
	next = g_gl.xec;
	if (!next)
		return ;
	while (next)
	{
		if (next->cmd[0])
			execute(next, p.paths_tab);
		next = next->link;
	}
	next = g_gl.xec;
	while (next)
	{
		if (next->in_fd != 0)
			close(next->in_fd);
		if (next->out_fd != 1)
			close(next->out_fd);
		next = next->link;
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
}
