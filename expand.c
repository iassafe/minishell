/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:42:44 by iassafe           #+#    #+#             */
/*   Updated: 2023/07/31 11:20:23 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_var_form(char *s, t_var	*p)
{
	while (s[p->i])
	{
		while (s[p->i] && (!ft_strchr("\"\'$", s[p->i])))
			p->i++;
		if (s[p->i] == '\'' && p->dq == 0)
		{
			p->i++;
			while (s[p->i] && s[p->i] != '\'')
				p->i++;
		}
		else if (s[p->i] == '\"' && p->sq == 0 && p->dq == 0)
		{
			p->dq = 1;
			p->i++;
			while (s[p->i] && s[p->i] != '$' && s[p->i] != '\"')
				p->i++;
			if (s[p->i] == '\"' )
				p->dq = 0;
		}
		if (s[p->i] == '$')
			break ;
		p->i++;
	}
}

char	*exp_condition(char *s, t_var *p)
{
	if (s[p->i] && ft_strchr("\"\'", s[p->i]) && p->dq == 0)
	{
		p->s2 = ft_substr(s, p->i, ft_strlen(s));
		s = ft_strjoin(ft_substr(s, 0, p->i - 1), p->s2);
	}
	else if (s[p->i] == '$' && s[p->i + 1] == '$')
	{
		while (s[p->i] == '$')
			p->i++;
	}
	else if (s[p->i - 1] && s[p->i] && ft_strchr("-*012345$6789@", s[p->i]))
	{
		p->i++;
		p->s1 = ft_substr(s, p->i, ft_strlen(s));
		s = ft_strjoin(ft_substr(s, 0, p->i - 2), p->s1);
		p->i--;
	}
	else if (s[p->i - 1] && s[p->i] && (ft_isalpha(s[p->i]) || s[p->i] == '_'))
	{
		s = env_search(s, p->i, p->i);
		p->i = p->pos1 - 1;
	}
	return (s);
}

char	*special_ch(char *s)
{
	t_var	p;

	p.dq = 0;
	p.sq = 0;
	s = dollars(s, &p);
	p.i = 0;
	while (s[p.i])
	{
		check_var_form(s, &p);
		p.i++;
		if (s[p.i] == '\0')
			break ;
		s = exp_condition(s, &p);
	}
	return (s);
}

void	ft_expand(void)
{
	t_msh	*p;

	p = g_gl.msh;
	while (p)
	{
		if ((!ft_memcmp(p->exp, "env\0", 4)
				|| !ft_memcmp(p->exp, "cmd\0", 4)
				|| !ft_memcmp(p->exp, "opt\0", 4)))
			p->data = special_ch(p->data);
		p = p->link;
	}
}
