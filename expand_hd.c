/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:17:00 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/19 11:43:57 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name_heredoc(void)
{
	char		*n;
	int			i;
	char		*name;
	char		*str;
	struct stat	file_info;

	name = "/tmp/heredoc";
	name = ft_strdup(name);
	n = "/tmp/heredoc";
	i = 0;
	while (!stat(name, &file_info))
	{
		str = ft_itoa(i);
		name = ft_strjoin(n, str);
		i++;
	}
	return (name);
}

char	*count_dollars_hd(char *s, t_var *p)
{
	p->i = 0;
	while (s[p->i])
	{
		p->n = 0;
		p->pos = p->i;
		while (s[p->i] == '$')
		{
			p->n++;
			p->i++;
		}
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
		p->i++;
	}
	return (s);
}

int	*check_var_form_hd(char *s, t_var *p)
{
	while (s[p->i])
	{
		while (s[p->i] && (!ft_strchr("\"\'$", s[p->i])))
			p->i++;
		if (s[p->i] == '\0')
			break ;
		if ((s[p->i] == '\"' || (s[p->i] == '\'')))
		{
			p->ch = s[p->i];
			p->i++;
			while (s[p->i] && s[p->i] != '$' && s[p->i] != p->ch)
				p->i++;
		}
		if (s[p->i] == '$')
			return (&p->i);
		p->i++;
	}
	return (&p->i);
}

char	*exp_condition_hd(t_msh *x, char *s, t_var *p, int *pos_i)
{
	if (s[p->i] && ft_strchr("\"\'", s[p->i]))
		p->i++;
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
	else if (s[p->i - 1] && s[p->i] == '?')
	{
		p->i++;
		p->s1 = ft_substr(s, p->i, ft_strlen(s));
		s = ft_strjoin3(ft_substr(s, 0, p->i - 2), ft_itoa(g_gl.exit), p->s1);
	}
	else
		p->i++;
	pos_i = &p->i;
	return (s);
}

char	*expand_hd(char *s)
{
	t_var	p;
	int		*pos_i;

	s = count_dollars_hd(s, &p);
	p.i = 0;
	pos_i = &p.i;
	while (s[p.i])
	{
		pos_i = check_var_form_hd(s, &p);
		p.i = *pos_i;
		p.i++;
		s = exp_condition_hd(NULL, s, &p, pos_i);
		p.i = *pos_i - 1;
	}
	return (s);
}
