/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:08:57 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/13 16:06:48 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_exec *next)
{
	char	*xec_path;
	char	**paths_tab;
	int		i;

	i = 0;
	paths_tab = get_paths();
	while (paths_tab[i])
	{
		xec_path = ft_strjoin3(paths_tab[i], "/", next->cmd[0]);
		if (xec_path && access(xec_path, X_OK) == 0)
		{
			execve(xec_path, next->cmd, copy_env());
			exit(1);
		}
		i++;
	}
	if (!paths_tab[i])
	{
		ft_putstr (ft_strjoin3("minishell: ", next->cmd[0], \
		": command not found\n"), 2);
		exit(127);
	}
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
		exit (1);
	if (next->pid == 0)
	{
		if (check_builtins(next->cmd[0]))
		{
			ft_builtins(next);
			exit(0);
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
			close(next->link->in_fd);
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
		if (next->cmd[0])
		{
			if (check_builtins(next->cmd[0]) && !next->prev && !next->link)
				ft_builtins(next);
			else
				execute(next);
		}
		next = next->link;
	}
	close_fd(g_gl.xec);
	while (waitpid(-1, &status, 0) != -1)
		;
	signals_handler(status);
}
