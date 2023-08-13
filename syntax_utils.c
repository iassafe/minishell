/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 13:28:37 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/13 14:51:57 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_char(char *s, int pos, t_var *p)
{
	if (s[pos] == '\"')
	{
		p->dq++;
		while (s[pos] && s[pos] != '\"')
			pos++;
		if (s[pos] && s[pos] == '\"')
			p->dq++;
	}
	else if (s[pos] == '\'')
	{
		p->sq++;
		while (s[pos] && s[pos] != '\'')
			pos++;
		if (s[pos] && s[pos] == '\'')
			p->sq++;
	}
	else if (s[pos] != 32 && (s[pos] < 9 || s[pos] > 13) && s[pos] != '|')
		p->ch++;
}

int	before(char *s, int pos, char c, t_var *p)
{
	if (pos == 0 || s[pos + 1] == '\0')
		return (1);
	pos--;
	while (pos >= 0 && s[pos] != c)
	{
		check_char(s, pos, p);
		pos--;
	}
	if ((p->dq == 0 && p->sq == 0 && p->ch == 0) \
		|| (p->dq && (p->dq % 2)) || (p->sq && (p->sq % 2)))
		return (1);
	return (0);
}

int	after(char *s, int pos, char c, t_var *p)
{
	pos++;
	if ((s[pos] == c || (c == '<')) || ((c == '>')))
	{
		while (s[pos] == 32)
			pos++;
		if (((s[pos] == '|' || s[pos] == c || s[pos] == '<') && c == '>')
			|| ((s[pos] == '|' || s[pos] == '>') && c == '<')
			|| (s[pos] == '|' && c == '>' && s[pos - 2] == '>'))
			return (1);
	}
	while (s[pos] && s[pos] != c)
	{
		check_char(s, pos, p);
		pos++;
	}
	if ((p->dq == 0 && p->sq == 0 && p->ch == 0) \
		|| (p->dq && p->dq % 2) || (p->sq && p->sq % 2))
		return (1);
	return (0);
}

int	check_others(char *s, int i)
{
	t_var	p;

	p.ch = 0;
	p.dq = 0;
	p.sq = 0;
	if (s[i] == '>' || s[i] == '<')
	{
		if ((s[i] == '>' && (after(s, i, '>', &p)))
			|| (s[i] == '<' && (after(s, i, '<', &p))))
			return (1);
	}
	else if (s[i] == '|')
	{
		if (before(s, i, '|', &p))
			return (1);
		p.dq = 0;
		p.sq = 0;
		p.ch = 0;
		if (after(s, i, '|', &p))
			return (1);
	}
	return (0);
}

int	doubles(char *s)
{
	int		i;
	char	c;

	i = 0;
	if (ft_strchr("\"\'", s[i]))
	{
		c = s[i];
		i++;
		while (s[i] && s[i] != c)
			i++;
		if (s[i] != c)
			return (1);
	}
	return (0);
}
