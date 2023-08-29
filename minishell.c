/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:11:26 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/19 16:34:44 by iassafe          ###   ########.fr       */
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
		new->ch_val = 0;
		new->link = NULL;
		if (g_gl.msh == NULL)
			g_gl.msh = new;
		else
			ptr->link = new;
		ptr = new;
		i++;
	}
}

void	ft_assayfo(t_var *v)
{
	v->tab = ft_split(v->line);
	ft_alloc_tab(v->tab);
	ft_alloc(v->tab);
	make_list(v->tab, NULL, NULL);
	ft_expand();
	no_expanded();
	ft_ignore();
	g_gl.xec = exec_list(NULL, NULL, NULL);
	if (g_gl.ctrl_c == 1)
		return ;
	ft_execution();
}

void	init_var(t_var *v, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	v->env = env;
	g_gl.em_e = 0;
	g_gl.exit = 0;
}

int	main(int ac, char **av, char **env)
{
	t_var	v;

	init_var(&v, ac, av, env);
	signal(SIGQUIT, SIG_IGN);
	getcwd(g_gl.pwd, sizeof(g_gl.pwd));
	list_env(v.env, NULL, NULL);
	while (1)
	{
		rl_catch_signals = 0;
		signal(SIGINT, sigint_handler);
		v.line = readline("minishell$: ");
		if (!v.line)
			ctrl_d();
		add_history(v.line);
		alloc_list(v.line);
		if (check_syntax(v.line))
		{
			write (2, "Syntax Error\n", 13);
			g_gl.exit = 258;
		}
		else
			ft_assayfo(&v);
		free_list();
	}
	free_list_env();
}
