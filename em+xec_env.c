/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   em+xec_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:37:50 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/17 18:34:54 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node(t_env *new, char *var, char *value)
{
	t_env	*next;

	while (new->link)
		new = new->link;
	next = malloc(sizeof(t_env));
	if (!next)
		return ;
	alloc_list_env(new);
	next->var = var;
	next->value = value;
	next->link = NULL;
	next->prev = new;
	new->link = next;
}

void	ft_create_node(t_env *new)
{
	g_gl.em_e = 1;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	alloc_list_env(new);
	new->var = "OLDPWD";
	new->value = NULL;
	new->link = NULL;
	new->prev = NULL;
	g_gl.env = new;
	add_node(new, "PWD\0", g_gl.pwd);
	add_node(new, "SHLVL\0", "1\0");
	add_node(new, "_\0", "/usr/bin/env\0");
	add_node(new, "PATH\0", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.\0");
}

void	print_env(char *var, char *value, int fd)
{
	ft_putstr(var, fd);
	write(fd, "=", 1);
	ft_putstr(value, fd);
	write(fd, "\n", 1);
}

void	xec_env(t_exec *x)
{
	t_env	*next;
	int		i;

	i = 0;
	next = g_gl.env;
	if (x->cmd[1])
	{
		ft_putstr("env: ", 2);
		ft_putstr(x->cmd[1], 2);
		ft_putstr(": No such file or directory\n", 2);
		g_gl.exit = 127;
	}
	else
	{
		while (next)
		{
			if (!ft_memcmp("PATH", next->var, 5) && g_gl.em_e == 1)
				i++;
			else if (next->value)
				print_env(next->var, next->value, x->out_fd);
			next = next->link;
		}
		g_gl.exit = 0;
	}
}
