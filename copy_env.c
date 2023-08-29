/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 13:37:42 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/18 16:27:42 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_new(t_env	*new, char **env, int i)
{
	int		j;
	int		nb;

	j = 0;
	while (env[i][j] != '=')
		j++;
	new->var = ft_substr1(env[i], 0, j);
	if (!ft_memcmp(new->var, "SHLVL", 6))
	{
		nb = ft_atoi(ft_substr1(env[i], j + 1, ft_strlen(env[i])));
		if (nb < 0)
			new->value = "0";
		else if (nb < 999)
			new->value = ft_itoa1(nb + 1);
		else if (nb == 999)
			new->value = "";
		else
			new->value = "1";
	}
	else
		new->value = ft_substr1(env[i], j + 1, ft_strlen(env[i]));
	new->link = NULL;
}

void	list_env(char **env, t_env *next, t_env	*new)
{
	int		i;

	i = 0;
	if (!env[i])
		ft_create_node(new);
	while (env[i])
	{
		new = malloc(sizeof (t_env));
		if (!new)
			return ;
		alloc_list_env(new);
		init_new(new, env, i);
		if (g_gl.env == NULL)
		{
			new->prev = NULL;
			g_gl.env = new;
		}
		else
		{
			new->prev = next;
			next->link = new;
		}
		next = new;
		i++;
	}
}

int	env_size(void)
{
	int		i;
	t_env	*env;

	env = g_gl.env;
	i = 0;
	while (env)
	{
		if (env->value)
			i++;
		env = env->link;
	}
	return (i);
}

char	**copy_env(void)
{
	t_env	*env;
	int		i;
	char	**c_env;

	i = env_size();
	c_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!c_env)
		return (NULL);
	ft_alloc(c_env);
	env = g_gl.env;
	i = 0;
	while (env)
	{
		if (env->value)
		{
			if (!(g_gl.em_e == 1 && !ft_memcmp(env->var, "PATH", 5)))
			{
				c_env[i] = ft_strdup(ft_strjoin3(env->var, "=", env->value));
				i++;
			}
		}
		env = env->link;
	}
	c_env[i] = NULL;
	return (c_env);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*p;
	int		l1;
	int		l2;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s1)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!p)
		return (0);
	alloc_list_env(p);
	ft_memcpy(p, s1, l1);
	ft_memcpy(p + l1, s2, l2 + 1);
	return (p);
}
