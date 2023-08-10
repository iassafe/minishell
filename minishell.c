/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:11:26 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/10 09:37:29 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gl	g_gl = {0};

void	make_list(char **tab, t_msh	*new, t_msh	*ptr)
{
	int		i;

	i = 0;
	ptr = g_gl.msh;
	while (tab[i])
	{
		new = malloc(sizeof(t_msh));
		if (!new)
			return ;
		ft_alloc(new);
		new->data = tab[i];
		if (i == 0)
			new->exp = get_type(tab[i], i, NULL);
		else
			new->exp = get_type(tab[i], i, ptr->exp);
		new->q_del = 0;
		new->q_empty = 0;
		new->link = NULL;
		if (g_gl.msh == NULL)
			g_gl.msh = new;
		else
			ptr->link = new;
		ptr = new;
		i++;
	}
}

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
		new->value = ft_itoa1(nb + 1);
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

void	ft_mini(t_var *v)
{
	t_exec		*x;

	x = NULL;
	v->tab = ft_split(v->line);
	ft_alloc_tab(v->tab);
	ft_alloc(v->tab);
	make_list(v->tab, NULL, NULL);
	ft_expand();
	ft_ignore();
	x = exec_list(x, x, NULL);
	ft_builtins(x);
}

int	main(int ac, char **av, char **env)
{
	t_var		v;

	(void)ac;
	(void)av;
	v.env = env;
	v.egal = 0;
	g_gl.em_e = 0;
	getcwd(g_gl.pwd, sizeof(g_gl.pwd));
	list_env(v.env, g_gl.env, NULL);
	while (1)
	{
		v.line = readline("minishell$: ");
		if (!v.line)
			return (0);
		add_history(v.line);
		alloc_list(v.line);
		if (check_syntax(v.line))
			write (2, "Syntax Error\n", 13);
		else
			ft_mini(&v);
		free_list();
	}
	free_list_env();
	exit (0);
}
