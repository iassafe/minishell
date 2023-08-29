/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:51:30 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/19 12:26:06 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_ofile(t_exec *x)
{
	if (x->out_fd != 1)
		close(x->out_fd);
	if (!ft_memcmp(g_gl.msh->link->exp, "env", 4))
	{
		if (!g_gl.msh->link->data)
		{
			ft_error("minishell: ambiguous redirect");
			g_gl.exit = 1;
			while (g_gl.msh && ft_memcmp(g_gl.msh->exp, "pipe", 5))
				g_gl.msh = g_gl.msh->link;
			return ;
		}
	}
	if (g_gl.msh->link->data && g_gl.msh->link->data[0] == '\0')
	{
		ft_putstr("minishell: : No such file or directory\n", 2);
		g_gl.exit = 1;
		while (g_gl.msh && ft_memcmp(g_gl.msh->exp, "pipe", 5))
			g_gl.msh = g_gl.msh->link;
		return ;
	}
	x->out_fd = open(g_gl.msh->link->data, O_RDWR | O_TRUNC | O_CREAT, 0644);
	g_gl.msh = g_gl.msh->link->link;
}

void	open_append(t_exec *x)
{
	if (x->out_fd != 1)
		close(x->out_fd);
	if (!ft_memcmp(g_gl.msh->link->exp, "env", 4))
	{
		if (!g_gl.msh->link->data)
		{
			ft_error("minishell: ambiguous redirect");
			g_gl.exit = 1;
			while (g_gl.msh && ft_memcmp(g_gl.msh->exp, "pipe", 5))
				g_gl.msh = g_gl.msh->link;
			return ;
		}
	}
	if (g_gl.msh->link->data && g_gl.msh->link->data[0] == '\0')
	{
		ft_putstr("minishell: : No such file or directory\n", 2);
		g_gl.exit = 1;
		while (g_gl.msh && ft_memcmp(g_gl.msh->exp, "pipe", 5))
			g_gl.msh = g_gl.msh->link;
		return ;
	}
	x->out_fd = open(g_gl.msh->link->data, O_RDWR | O_APPEND | O_CREAT, 0644);
	g_gl.msh = g_gl.msh->link->link;
}

void	open_infile(t_exec *x)
{
	if (x->in_fd > 0)
		close(x->in_fd);
	x->in_fd = open(g_gl.msh->link->data, O_RDONLY, 0644);
	if (!ft_memcmp(g_gl.msh->link->exp, "env", 4) || x->in_fd < 0)
	{
		if ((!ft_memcmp(g_gl.msh->link->exp, "env", 4) \
		&& !g_gl.msh->link->data) || g_gl.msh->ch_val == 1)
		{
			ft_error("minishell: ambiguous redirect");
			g_gl.exit = 1;
		}
		else if (x->in_fd < 0)
		{
			ft_putstr("minishell : ", 2);
			perror(g_gl.msh->link->data);
			g_gl.exit = 1;
		}
		while (g_gl.msh && ft_memcmp(g_gl.msh->exp, "pipe", 5) 
			&& ft_memcmp(g_gl.msh->exp, "h_doc", 6))
			g_gl.msh = g_gl.msh->link;
		return ;
	}
	g_gl.msh = g_gl.msh->link->link;
}

void	open_h_doc(t_exec *x)
{
	char	*line;
	char	*name;
	int		fd;

	g_gl.ctrl_c = 0;
	fd = dup(0);
	name = name_heredoc();
	signal(SIGINT, sig_herdoc);
	x->in_fd = open(name, O_RDWR | O_CREAT, 0644);
	line = readline("> ");
	quit_herdoc(line, fd);
	ft_alloc(line);
	while (line && g_gl.msh && g_gl.msh->link && ft_memcmp(line, \
	g_gl.msh->link->data, ft_strlen(g_gl.msh->link->data) + ft_strlen(line)))
		line = wr_herdoc(line, x->in_fd, fd);
	close(x->in_fd);
	if (g_gl.ctrl_c == 1)
	{
		while (g_gl.msh)
			g_gl.msh = g_gl.msh->link;
		return ;
	}
	x->in_fd = open(name, O_RDONLY);
	g_gl.msh = g_gl.msh->link->link;
}

void	new_init(t_exec *x)
{
	int		i;

	i = 0;
	while (g_gl.msh && (ft_memcmp(g_gl.msh->exp, "pipe", 7)))
	{
		while (g_gl.msh && (!ft_memcmp(g_gl.msh->exp, "cmd", 4) || \
	!ft_memcmp(g_gl.msh->exp, "opt", 4) || !ft_memcmp(g_gl.msh->exp, "env", 4)))
		{
			if (g_gl.msh->data)
				x->cmd[i++] = ft_strdup(g_gl.msh->data);
			g_gl.msh = g_gl.msh->link;
		}
		x->cmd[i] = NULL;
		if (g_gl.msh && !ft_memcmp(g_gl.msh->exp, "o_file", 7))
			open_ofile(x);
		else if (g_gl.msh && !ft_memcmp(g_gl.msh->exp, "append", 7))
			open_append(x);
		else if (g_gl.msh && !ft_memcmp(g_gl.msh->exp, "infile", 7))
			open_infile(x);
		else if (g_gl.msh && !ft_memcmp(g_gl.msh->exp, "h_doc", 6))
			open_h_doc(x);
	}
	if (g_gl.msh && !ft_memcmp(g_gl.msh->exp, "pipe", 5))
		g_gl.msh = g_gl.msh->link;
}
