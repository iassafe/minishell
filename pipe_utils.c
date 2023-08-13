/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:50:34 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/13 11:00:43 by iassafe          ###   ########.fr       */
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

void	execute(t_exec *next)
{
	if (next->cmd[0][0] == '\0')
	{
		ft_putstr (ft_strjoin3("minishell: ", next->cmd[0], \
		": command not found\n"), 2);
	}
	else
		open_pipe(next);
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

void	signals_handler(void)
{
	int	status;

	if (WIFEXITED(status))
		g_gl.exit = status;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3 || WTERMSIG(status) == 2)
		{
			g_gl.exit = WTERMSIG(status) + 128;
			if (WTERMSIG(status) == 3)
				printf("Quit: %d\n", WTERMSIG(status));
			else
				printf("\n");
		}
	}
}

void	close_fd(t_exec *head)
{
	t_exec	*next;

	next = head;
	while (next)
	{
		if (next->in_fd != 0)
			close(next->in_fd);
		if (next->out_fd != 1)
			close(next->out_fd);
		next = next->link;
	}
}
