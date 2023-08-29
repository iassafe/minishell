/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:08:57 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/19 12:06:55 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_exec *next)
{
	char	**paths_tab;

	paths_tab = get_paths();
	if (check_slash(next->cmd[0]))
	{
		if (access(next->cmd[0], F_OK) != 0)
			g_gl.exit = 127;
		else if (access(next->cmd[0], X_OK) != 0)
			g_gl.exit = 126;
		else if (check_dir(next->cmd[0]))
		{
			g_gl.exit = 126;
			ft_putstr(ft_strjoin3("minishell: ", next->cmd[0], \
			": is a directory\n"), 2);
			exit(g_gl.exit);
		}
		execve(next->cmd[0], next->cmd, copy_env());
		perror("minishell ");
		exit(g_gl.exit);
	}
	else
		searching_path(next, paths_tab);
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

void	ft_child(t_exec *next)
{
	next->pid = fork();
	if (next->pid < 0)
	{
		ft_putstr("fork failed\n", 2);
		exit (1);
	}
	if (next->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (check_builtins(next->cmd[0]))
		{
			ft_builtins(next);
			exit(g_gl.exit);
		}
		else
		{
			ft_dup(next);
			execute_cmd(next);
		}
	}
}

void	open_pipe(t_exec *next)
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
		{
			close(p.pipe_end[0]);
			close(next->link->in_fd);
		}
	}
	ft_child(next);
}

void	ft_execution(void)
{
	t_exec	*next;
	int		status;

	next = g_gl.xec;
	if (!next)
		return ;
	while (next)
	{
		if (check_builtins(next->cmd[0]) && !next->prev && !next->link)
		{
			if (next->in_fd != -1)
				ft_builtins(next);
		}
		else
		{
			if (next->in_fd != -1)
				execute(next);
		}
		next = next->link;
	}
	close_fd(g_gl.xec);
	while (waitpid(-1, &status, 0) != -1)
		;
	signals_handler(status);
}
