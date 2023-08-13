/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:11:26 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/13 11:18:04 by iassafe          ###   ########.fr       */
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
	v->tab = ft_split(v->line);
	ft_alloc_tab(v->tab);
	ft_alloc(v->tab);
	make_list(v->tab, NULL, NULL);
	ft_expand();
	ft_ignore();
	g_gl.xec = exec_list(NULL, NULL, NULL);
	ft_execution();
}

void	sigint_handler(int si)
{
	int	status;

	(void)si;
	if (WIFSIGNALED(status))
		g_gl.exit = WIFSIGNALED(status);
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **av, char **env)
{
	t_var	v;

	(void)ac;
	(void)av;
	v.env = env;
	v.egal = 0;
	g_gl.em_e = 0;
	getcwd(g_gl.pwd, sizeof(g_gl.pwd));
	signal(SIGQUIT, SIG_IGN);
	list_env(v.env, g_gl.env, NULL);
	while (1)
	{
		rl_catch_signals = 0;
		signal(SIGINT, sigint_handler);
		v.line = readline("minishell$: ");
		if (!v.line)
		{
			printf("exit\n");
			g_gl.exit = 0;
			exit(0);
		}
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
