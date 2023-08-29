/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:42:44 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/19 15:41:23 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exp_condition2(char *s, t_var *p, int *pos_i)
{
	if (s[p->i] && ((s[p->i] == '\'' && p->dq == 0) || (s[p->i] == '\"')))
	{
		p->s2 = ft_substr(s, p->i, ft_strlen(s));
		s = ft_strjoin(ft_substr(s, 0, p->i - 1), p->s2);
	}
	else if (s[p->i] == '$' && s[p->i + 1] == '$')
	{
		while (s[p->i] == '$')
			p->i++;
	}
	else if (s[p->i - 1] && s[p->i] == '?' && p->sq == 0)
	{
		p->i++;
		p->s1 = ft_substr(s, p->i, ft_strlen(s));
		if (p->s1 == NULL)
			p->s1 = "";
		p->s2 = ft_substr(s, 0, p->i - 2);
		if (p->s2 == NULL)
			p->s2 = "";
		s = ft_strjoin3(p->s2, ft_itoa(g_gl.exit), p->s1);
	}
	pos_i = &p->i;
	return (s);
}

char	*exp_condition(t_msh *x, char *s, t_var *p, int *pos_i)
{
	if ((s[p->i] && ((s[p->i] == '\'' && p->dq == 0) || (s[p->i] == '\"'))) \
	|| (s[p->i] == '$' && s[p->i + 1] == '$') \
	|| (s[p->i - 1] && s[p->i] == '?' && p->sq == 0))
		s = exp_condition2(s, p, pos_i);
	else if (s[p->i - 1] && s[p->i] && ft_strchr("-*012345$6789@", s[p->i]))
	{
		p->i++;
		p->s1 = ft_substr(s, p->i, ft_strlen(s));
		s = ft_strjoin(ft_substr(s, 0, p->i - 2), p->s1);
	}
	else if (s[p->i - 1] && s[p->i] && (ft_isalpha(s[p->i]) || s[p->i] == '_'))
	{
		s = env_search(x, s, p->i, pos_i);
		p->i = *pos_i;
	}
	else
		p->i++;
	pos_i = &p->i;
	return (s);
}

char	*special_ch(t_msh *x, char *s, int *pos_i)
{
	t_var	p;

	p.dq = 0;
	p.sq = 0;
	s = dollars(s, &p);
	p.i = 0;
	pos_i = &p.i;
	while (s[p.i] && p.i >= 0)
	{
		pos_i = check_var_form(s, &p);
		p.i = *pos_i;
		p.i++;
		if (s[p.i] == '\0')
			break ;
		s = exp_condition(x, s, &p, pos_i);
		p.i = *pos_i - 1;
	}
	return (s);
}

void	ft_expand(void)
{
	t_msh	*p;

	p = g_gl.msh;
	while (p)
	{
		if ((!ft_memcmp(p->exp, "env", 4)
				|| !ft_memcmp(p->exp, "cmd", 4)
				|| !ft_memcmp(p->exp, "opt", 4)))
			p->data = special_ch(p, p->data, p->pos_i);
		p = p->link;
	}
}
