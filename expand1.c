/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:24:40 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/19 15:40:41 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_form(char *s, t_var *p)
{
	if ((s[p->i] == '\"' && p->dq == 0) || s[p->i] == '$')
	{
		if (s[p->i] == '\"' && p->dq == 0)
		{
			p->dq = 1;
			while (s[p->i] && s[p->i] != '$')
				p->i++;
		}
		p->pos = p->i;
		while (s[p->i] == '$')
			p->i++;
		p->n = p->i - p->pos;
	}
	else if (s[p->i] == '\'' && p->sq == 0)
	{
		p->i++;
		p->sq = 1;
		if (s[p->i] != '\'')
		{
			while (s[p->i] && s[p->i] != '\'')
				p->i++;
		}
	}
	return (s);
}

char	*cut_dollars(char *s, t_var *p)
{
	if (p->n && p->n % 2)
	{
		p->s1 = ft_substr(s, 0, p->pos + 1);
		p->s2 = ft_substr(s, p->i, ft_strlen(s));
		s = ft_strjoin(p->s1, p->s2);
	}
	else if (p->n && p->n != 2 && p->n % 2 == 0)
	{
		p->s1 = ft_substr(s, 0, p->pos + 2);
		p->s2 = ft_substr(s, p->i, ft_strlen(s));
		s = ft_strjoin(p->s1, p->s2);
	}
	return (s);
}

char	*dollars(char *s, t_var *p)
{
	p->sq = 0;
	p->dq = 0;
	p->i = 0;
	while (s[p->i])
	{
		p->n = 0;
		p->pos = p->i;
		s = check_form(s, p);
		if (s[p->i] == '\'' && p->sq == 1)
			p->sq = 0;
		else
			s = cut_dollars(s, p);
		if (p->dq == 1)
		{
			while (s[p->i] && s[p->i] != '$' && s[p->i] != '\"')
				p->i++;
			if (s[p->i] == '$')
				p->i--;
		}
		p->i++;
	}
	return (s);
}

char	*expanded_s(t_msh *x, char *s, t_var *p, int *pos_i)
{
	t_env	*c_env;

	c_env = g_gl.env;
	while (c_env)
	{
		p->j++;
		if (ft_memcmp(p->var1, c_env->var, (p->i)) == 0)
		{
			s = join_value(s, p->pos1, c_env, x);
			pos_i = &p->pos1;
			return (s);
		}
		c_env = c_env->link;
	}
	if (p->j == p->n)
	{
		s = ft_strjoin(ft_substr(s, 0, p->pos1 - 1), \
		ft_substr(s, p->pos, ft_strlen(s)));
		p->i = p->pos - p->i;
		pos_i = &p->i;
	}
	return (s);
}

char	*env_search(t_msh *x, char *s, int pos, int *pos_i)
{
	t_var	p;
	int		pos1;
	t_env	*c_env;

	p.i = 0;
	p.n = 0;
	pos1 = pos;
	c_env = g_gl.env;
	while (c_env)
	{
		p.n++;
		c_env = c_env->link;
	}
	while (s[pos] && (ft_isalnum(s[pos]) || s[pos] == '_'))
	{
		pos++;
		p.i++;
	}
	p.var1 = ft_substr(s, pos1, p.i);
	p.pos = pos;
	p.pos1 = pos1;
	p.j = 0;
	s = expanded_s(x, s, &p, pos_i);
	return (s);
}
