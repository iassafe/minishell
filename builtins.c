/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:00:20 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/18 18:20:09 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	xec_pwd(t_exec *x)
{
	char	*pwd;

	pwd = getcwd(g_gl.pwd, sizeof(g_gl.pwd));
	if (!pwd && !access(g_gl.pwd, F_OK))
	{
		ft_putstr("Error\n", 2);
		g_gl.exit = 1;
		return ;
	}
	ft_putstr(g_gl.pwd, x->out_fd);
	write(x->out_fd, "\n", 1);
	g_gl.exit = 0;
}

void	print_export(int fd, t_env *next)
{
	ft_putstr("declare -x ", fd);
	ft_putstr(next->var, fd);
	if (next->value)
	{
		write(fd, "=\"", 2);
		ft_putstr(next->value, fd);
		write(fd, "\"", 1);
	}
	write(fd, "\n", 1);
}

void	xec_export(t_exec *x)
{
	t_env	*next;
	int		i;

	i = 0;
	next = g_gl.env;
	if (x->cmd[1])
		check_export(x);
	if (!x->cmd[1])
	{
		while (next)
		{
			if (g_gl.em_e == 1 && \
			(!ft_memcmp("_", next->var, 2) \
			|| !ft_memcmp("PATH", next->var, 5)))
				i++;
			else
				print_export(x->out_fd, next);
			next = next->link;
		}
		g_gl.exit = 0;
	}
}

void	xec_exit(t_exec *x)
{
	if (!x->cmd[1])
	{
		ft_putstr("exit\n", 2);
		g_gl.exit = 0;
		exit(0);
	}
	else
		check_arg(x);
}

void	ft_builtins(t_exec *x)
{
	t_var	v;

	if (x->cmd[0])
	{
		if (!ft_memcmp(x->cmd[0], "echo", 5))
			xec_echo(x, &v);
		else if (!ft_memcmp(x->cmd[0], "pwd", 4))
			xec_pwd(x);
		else if (!ft_memcmp(x->cmd[0], "env", 4))
			xec_env(x);
		else if (!ft_memcmp(x->cmd[0], "export", 7))
			xec_export(x);
		else if (!ft_memcmp(x->cmd[0], "unset", 6))
			xec_unset(x);
		else if (!ft_memcmp(x->cmd[0], "cd", 3))
			xec_cd(x);
		else if (!ft_memcmp(x->cmd[0], "exit", 4))
			xec_exit(x);
	}
}
