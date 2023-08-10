/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:17:00 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/09 11:10:43 by iassafe          ###   ########.fr       */
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

void	check_var_form_hd(char *s, t_var *p)
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
			break ;
		p->i++;
	}
}

char	*exp_condition_hd(char *s, t_var *p)
{
	if (s[p->i] && ft_strchr("\"\'", s[p->i]))
		p->i++;
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

char	*expand_hd(char *s)
{
	t_var	p;

	s = count_dollars_hd(s, &p);
	p.i = 0;
	while (s[p.i])
	{
		check_var_form_hd(s, &p);
		p.i++;
		s = exp_condition_hd(s, &p);
	}
	return (s);
}
