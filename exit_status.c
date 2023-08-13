/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:21:14 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/13 17:41:05 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(void)
{
	t_exec	*x;
	t_var	v;

	x = g_gl.xec;
	while (x)
	{
		v.i = 0;
		while (x->cmd[v.i])
		{
			v.j = 0;
			while (x->cmd[v.i][v.j])
			{
				if (x->cmd[v.i][v.j] == '$' && x->cmd[v.i][v.j + 1] == '?')
				{
					v.s1 = ft_substr(x->cmd[v.i], 0, v.j);
					v.s2 = ft_substr(x->cmd[v.i], v.j + 2, \
							ft_strlen(x->cmd[v.i]));
					x->cmd[v.i] = ft_strjoin3(v.s1, ft_itoa(g_gl.exit), v.s2);
				}
				v.j++;
			}
			v.i++;
		}
		x = x->link;
	}
}
