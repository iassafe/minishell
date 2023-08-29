/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:19:29 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/19 15:20:48 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*check_var_form(char *s, t_var *p)
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
			if (s[p->i] == '\"')
				p->dq = 0;
		}
		if (s[p->i] == '$')
			return (&p->i);
		p->i++;
	}
	return (&p->i);
}

void	no_expanded(void)
{
	t_msh	*next;

	next = g_gl.msh;
	while (next)
	{
		if (next->data[0] == '\0')
			next->data = NULL;
		next = next->link;
	}
}

void	check_value(t_msh *x, char *value)
{
	int	i;

	i = 0;
	if (x == NULL)
		return ;
	while (value[i] && value[i] != ' ' && value[i] != '\t')
		i++;
	if (value[i] == ' ' || value[i] == '\t')
		x->ch_val = 1;
}

char	*join_value(char *s, int pos1, t_env *c_env, t_msh *x)
{
	char	*s1;
	char	*s2;

	if (!c_env->value)
	{
		s = ft_strjoin3(ft_substr(s, 0, pos1 - 1), "", \
		ft_substr(s, pos1 + ft_strlen(c_env->var), ft_strlen(s)));
	}
	else
	{
		s1 = ft_substr(s, 0, pos1 - 1);
		if (s1 == NULL)
			s1 = "";
		s2 = ft_substr(s, pos1 + ft_strlen(c_env->var), ft_strlen(s));
		if (s2 == NULL)
			s2 = "";
		s = ft_strjoin3(s1, c_env->value, s2);
		check_value(x, c_env->value);
	}
	return (s);
}
