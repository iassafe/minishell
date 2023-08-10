/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:36:18 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/09 15:25:27 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_msh	*head)
{
	t_msh	*next;
	int		i;

	i = 0;
	next = head;
	while (next && (ft_memcmp(next->exp, "infile", 7)
			&& ft_memcmp(next->exp, "o_file", 7)
			&& ft_memcmp(next->exp, "pipe", 5)))
	{
		i++;
		next = next->link;
	}
	return (i + 1);
}

void	ft_init(t_exec *new)
{
	new->in_fd = 0;
	new->out_fd = 1;
	new->quo = 0;
	new->link = NULL;
}

t_exec	*exec_list(t_exec *x, t_exec *tmp, t_exec *new)
{
	while (g_gl.msh)
	{
		new = malloc(sizeof(t_exec));
		if (!new)
			return (NULL);
		ft_alloc(new);
		new->cmd = malloc(sizeof(char *) * (count_cmd(g_gl.msh)));
		if (!new->cmd)
			return (NULL);
		ft_alloc(new->cmd);
		ft_init(new);
		new_init(new);
		if (x == NULL)
		{
			new->prev = NULL;
			x = new;
		}
		else
		{
			tmp->link = new;
			new->prev = tmp;
		}
		tmp = new;
	}
	return (x);
}
