/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:03:20 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/19 09:50:23 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cut(char *s, t_var *p, char c)
{
	int		fir;

	fir = p->i;
	p->i++;
	while (s[p->i] && s[p->i] != c)
		p->i++;
	p->s1 = ft_substr(s, 0, fir);
	p->s2 = ft_substr(s, fir + 1, p->i - fir - 1);
	p->s3 = ft_substr(s, p->i + 1, (ft_strlen(s) - p->i));
	s = ft_strjoin(p->s1, p->s2);
	s = ft_strjoin(s, p->s3);
	return (s);
}

void	ft_ignore(void)
{
	t_msh	*next;
	t_var	p;
	char	c;

	next = g_gl.msh;
	while (next)
	{
		p.i = 0;
		if (next->data)
		{
			while (next->data[p.i])
			{
				if (next->data[p.i] == '\"' || next->data[p.i] == '\'')
				{
					if (!ft_memcmp(next->exp, "del", 4))
						next->q_del = 1;
					c = next->data[p.i];
					next->data = ft_cut(next->data, &p, c);
					p.i -= 2;
				}
				p.i++;
			}
		}
		next = next->link;
	}
}
