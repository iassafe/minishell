/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:50:34 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/19 14:30:31 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cmd(t_exec *next)
{
	int	i;

	i = 0;
	if (next->ch_val == 1)
	{
		while (next->cmd[0] && next->cmd[0][i] != ' ' && \
			next->cmd[0][i] != '\t' && next->cmd[0][i])
			i++;
		if (next->cmd[0][i])
			return (ft_substr(next->cmd[0], 0, i));
	}
	return (next->cmd[0]);
}

void	searching_path(t_exec *next, char **paths_tab)
{
	char	*xec_path;
	int		i;

	i = 0;
	while (paths_tab && paths_tab[i])
	{
		xec_path = ft_strjoin3(paths_tab[i], "/", ft_cmd(next));
		if (xec_path && access(xec_path, X_OK) == 0)
		{
			execve(xec_path, next->cmd, copy_env());
			perror("minishell ");
			exit(1);
		}
		i++;
	}
	if (!paths_tab || !paths_tab[i])
	{
		if (paths_tab && !paths_tab[i])
			ft_putstr (ft_strjoin3("minishell: ", ft_cmd(next), \
		": command not found\n"), 2);
		else
			ft_putstr (ft_strjoin3("minishell: ", ft_cmd(next), \
		": No such file or directory\n"), 2);
		exit(127);
	}
}

void	execute(t_exec *next)
{
	if (next->cmd[0] && next->cmd[0][0] == '\0')
	{
		ft_putstr (ft_strjoin3("minishell: ", next->cmd[0], \
		": command not found\n"), 2);
		g_gl.exit = 127;
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
			return (paths_tab);
		}
		next = next->link;
	}
	return (NULL);
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
