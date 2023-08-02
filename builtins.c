/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:00:20 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/02 09:56:25 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_exec *x, t_var *v)
{
	v->i = 1;
	v->n = 0;
	while (x->cmd[v->i] && x->cmd[v->i][0] == '-' && x->cmd[v->i][1] == 'n')
	{
		v->d = 1;
		while (x->cmd[v->i] && x->cmd[v->i][v->d] == 'n')
			v->d++;
		if (!x->cmd[v->i][v->d])
		{
			v->i++;
			v->n = 1;
		}
		else
			break ;
	}
	while (x->cmd[v->i])
	{
		ft_putstr(x->cmd[v->i], x->out_fd);
		if (x->cmd[v->i + 1])
			write(x->out_fd, " ", 1);
		v->i++;
	}
	if (v->n == 0)
		write(x->out_fd, "\n", 1);
}

void	exec_pwd(t_exec *x)
{
	char	*pwd;

	pwd = getcwd(g_gl.pwd, sizeof(g_gl.pwd));
	if (!pwd)
	{
		perror("getcwd");
		return ;
	}
	ft_putstr(pwd, x->out_fd);
	write(x->out_fd, "\n", 1);
}

void	exec_env(t_exec *x)
{
	if (x->cmd[1] && x->cmd[1][0] != '\0' && x->quo == 1)
	{
		ft_putstr("env: ", 2);
		ft_putstr(x->cmd[1], 2);
		ft_putstr(": No such file or directory\n", 2);
	}
	else
	{
		while (g_gl.env)
		{
			ft_putstr(g_gl.env->var, x->out_fd);
			write(x->out_fd, "=", 1);
			ft_putstr(g_gl.env->value, x->out_fd);
			write(x->out_fd, "\n", 1);
			g_gl.env = g_gl.env->link;
		}
	}
}

void	ft_builtins(t_exec *x)
{
	t_var	v;

	while (x)
	{
		if (!ft_memcmp(x->cmd[0], "echo\0", 5)
			|| !ft_memcmp(x->cmd[0], "ECHO\0", 5))
			exec_echo(x, &v);
		else if (!ft_memcmp(x->cmd[0], "pwd\0", 4)
			|| !ft_memcmp(x->cmd[0], "PWD\0", 4))
			exec_pwd(x);
		else if (!ft_memcmp(x->cmd[0], "env\0", 4)
			|| !ft_memcmp(x->cmd[0], "ENV\0", 4))
			exec_env(x);
		x = x->link;
	}
}
