/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:29:10 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/18 15:53:29 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_node(char *cmd, char *s, t_var *v, t_env *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	alloc_list_env(new);
	new->var = s;
	if (cmd[v->i] == '+')
		new->value = ft_substr1(cmd, v->i + 2, ft_strlen(cmd));
	else if (cmd[v->i] != '\0')
		new->value = ft_substr1(cmd, v->i + 1, ft_strlen(cmd));
	else
		new->value = NULL;
	new->prev = env;
	new->link = NULL;
	if (env == NULL)
	{
		g_gl.env = new;
		return ;
	}
	env->link = new;
}

t_env	*check_var(char *cmd, t_var *v, t_env *env)
{
	while (cmd[v->i] && cmd[v->i] != '=')
		v->i++;
	if (cmd[v->i] == '=' && cmd[v->i - 1] == '+')
	{
		v->n = 1;
		v->i--;
	}
	v->s1 = ft_substr1(cmd, 0, v->i);
	while (env && env->link)
	{
		if (!ft_memcmp(v->s1, env->var, v->i))
		{
			v->d = 1;
			break ;
		}
		env = env->link;
	}
	return (env);
}

void	add_in_env(char *cmd)
{
	t_env	*env;
	t_var	v;

	v.i = 0;
	v.d = 0;
	v.n = 0;
	env = check_var(cmd, &v, g_gl.env);
	if (env && !ft_memcmp(v.s1, env->var, v.i) && v.d == 0)
		v.d = 1;
	if (v.d == 1)
	{
		if (cmd[v.i] == '\0')
			return ;
		if (v.n == 1)
		{
			env->value = ft_strjoin1(env->value, \
				ft_substr1(cmd, v.i + 2, ft_strlen(cmd)));
		}
		else
			env->value = ft_substr1(cmd, v.i + 1, ft_strlen(cmd));
	}
	else
		add_new_node(cmd, v.s1, &v, env);
}

int	check_chr(char *cmd)
{
	int	i;

	i = 1;
	if (((cmd[0] == '\0') || cmd[0] == '\"' || cmd[0] == '\''))
		return (1);
	else if (!ft_isalpha(cmd[0]) && cmd[0] != '_'
		&& cmd[0] != '\0')
		return (1);
	while (cmd[i] != '\0' && cmd[i] != '=')
	{
		if (cmd[i] == '+' && cmd[i + 1] != '=')
			return (1);
		if (!ft_isalnum(cmd[i])
			&& cmd[i] != '_' && cmd[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

void	check_export(t_exec *x)
{
	int	i;

	i = 1;
	while (x->cmd[i])
	{
		if (check_chr(x->cmd[i]))
		{
			ft_putstr("minishell: export: `", 2);
			ft_putstr(x->cmd[i], 2);
			ft_putstr("': not a valid identifier\n", 2);
			g_gl.exit = 1;
		}
		else
		{
			add_in_env(x->cmd[i]);
			g_gl.exit = 0;
		}
		i++;
	}
}
