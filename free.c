/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanhayf <khanhayf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:02:14 by khanhayf          #+#    #+#             */
/*   Updated: 2023/07/20 11:57:24 by khanhayf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_list(void *line)
{
	g_gl.f = malloc(sizeof(t_free));
	if (!g_gl.f)
		return ;
	g_gl.f->ptr = line;
	g_gl.f->link = NULL;
}

void	ft_alloc(void *p)
{
	t_free	*next;
	t_free	*new;

	next = g_gl.f;
	new = NULL;
	while (next->link)
		next = next->link;
	new = malloc(sizeof(t_free));
	if (!new)
		return ;
	new->ptr = p;
	new->link = NULL;
	next->link = new;
}

void	ft_alloc_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_alloc(tab[i]);
		i++;
	}
}

void	free_list(void)
{
	t_free	*next;

	while (g_gl.f)
	{
		free (g_gl.f->ptr);
		next = g_gl.f->link;
		free(g_gl.f);
		g_gl.f = next;
	}
}
