/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:30:40 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/15 14:31:37 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rows_check_char(char *s, int i, t_var *p, char ch)
{
	if (s[i] == '|' || s[i] == '>' || s[i] == '<')
	{
		p->n++;
		if ((s[i] == '>' && s[i + 1] && s[i + 1] == '>')
			|| (s[i] == '<' && s[i + 1] && s[i + 1] == '<'))
			i++;
		i++;
	}
	else if (!ft_strchr(" \t\v\r\f", s[i]))
	{
		p->n++;
		while (s[i] && !ft_strchr("><| \t\v\r\f", s[i]))
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				ch = s[i++];
				while (s[i] && s[i] != ch)
					i++;
			}
			i++;
		}
	}
	else
		i++;
	return (i);
}

int	c_rows(char *s)
{
	int		i;
	t_var	p;

	p.n = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i = rows_check_char(s, i, &p, '\0');
	return (p.n + 1);
}

int	col_check_char(char *s, int i, char ch)
{
	if (s[i] == '|' || s[i] == '>' || s[i] == '<')
	{
		if ((s[i] == '>' && s[i + 1] == '>')
			|| (s[i] == '<' && s[i + 1] == '<'))
			i++;
		i++;
	}
	else if (!ft_strchr(" \t\v\r\f", s[i]))
	{
		while (s[i] && !ft_strchr("><| \t\v\r\f", s[i]))
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				ch = s[i++];
				while (s[i] && s[i] != ch)
					i++;
			}
			i++;
		}
	}
	else
		i++;
	return (i);
}

char	**c_col(char **tab, char *s)
{
	char	*tmp;
	int		j;

	j = 0;
	while (*s)
	{
		if (*s && !ft_strchr(" \t\v\r\f", *s))
		{
			tmp = s;
			s += col_check_char(s, 0, '\0');
			tab[j] = (char *)malloc(sizeof(char) * ((s - tmp) + 1));
			if (tab[j] == NULL)
			{
				release (tab);
				return (NULL);
			}
			ft_memcpy(tab[j], tmp, (s - tmp));
			tab[j++][s - tmp] = '\0';
		}
		else
			s++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char *s)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * c_rows(s));
	if (tab == NULL)
		return (NULL);
	tab = c_col(tab, s);
	return (tab);
}
