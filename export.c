/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:29:10 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/09 17:21:00 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_node(char *cmd, char *s, t_var *v, t_env *env)
{
	t_env	*new;

	new = NULL;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	ft_alloc(new);
	new->var = s;
	if (cmd[v->i] != '\0')
		new->value = ft_substr(cmd, v->i + 1, ft_strlen(cmd));
	else
		new->value = NULL;
	new->link = NULL;
	env->link = new;
	new->prev = env;
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
	v->s1 = ft_substr(cmd, 0, v->i);
	while (env->link)
	{
		if (!ft_memcmp(v->s1, env->var, ft_strlen(v->s1) + ft_strlen(env->var)))
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
	env = g_gl.env;
	env = check_var(cmd, &v, env);
	if (!ft_memcmp(v.s1, env->var, ft_strlen(v.s1) \
		+ ft_strlen(env->var)) && v.d == 0)
		v.d = 1;
	if (v.d == 1)
	{
		if (cmd[v.i] == '\0' && (!env->value || env->value))
			return ;
		if (v.n == 1)
			env->value = ft_strjoin(env->value, \
				ft_substr(cmd, v.i + 2, ft_strlen(cmd)));
		else
			env->value = ft_substr(cmd, v.i + 1, ft_strlen(cmd));
	}
	else
		add_new_node(cmd, v.s1, &v, env);
}

int	check_chr(char *cmd, t_exec *x)
{
	int	i;

	i = 1;
	if (((cmd[0] == '\0' && x->quo == 1) || (cmd[0] == '\"' || cmd[0] == '\'')))
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
		if (check_chr(x->cmd[i], x))
		{
			ft_putstr("minishell: export: `", 2);
			ft_putstr(x->cmd[i], 2);
			ft_putstr("': not a valid identifier\n", 2);
		}
		else
		{
			if (x->cmd[i][0] != '\0')
				add_in_env(x->cmd[i]);
		}
		i++;
	}
}
