/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:44:36 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/17 19:08:46 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	xec_echo(t_exec *x, t_var *v)
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
	g_gl.exit = 0;
}

void	delete_node(char *cmd)
{
	t_env	*env;

	env = g_gl.env;
	while (env)
	{
		if (!ft_memcmp(cmd, env->var, ft_strlen(cmd) + ft_strlen(env->var)))
		{
			if (env->prev && env->link)
			{
				env->link->prev = env->prev;
				env->prev->link = env->link;
			}
			else if (!env->prev && env->link)
			{
				g_gl.env = env->link;
				g_gl.env->prev = NULL;
			}
			else if (!env->prev && !env->link)
				g_gl.env = NULL;
			else if (env->prev && !env->link)
				env->prev->link = NULL;
			break ;
		}
		env = env->link;
	}
}

int	check_cmd(char *cmd)
{
	int	i;

	i = 1;
	if ((cmd[0] == '\0' || cmd[0] == '\"' || cmd[0] == '\''))
		return (1);
	else if (!ft_isalpha(cmd[0]) && cmd[0] != '_' && cmd[0] != '\0')
		return (1);
	while (cmd[i] != '\0')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	xec_unset(t_exec *x)
{
	int	i;

	if (x->cmd[1])
	{
		i = 1;
		while (x->cmd[i])
		{
			if (check_cmd(x->cmd[i]))
			{
				ft_putstr("minishell: unset: `", 2);
				ft_putstr(x->cmd[i], 2);
				ft_putstr("': not a valid identifier\n", 2);
				g_gl.exit = 1;
				return ;
			}
			else
			{
				delete_node(x->cmd[i]);
				g_gl.exit = 0;
			}
			i++;
		}
	}
}
