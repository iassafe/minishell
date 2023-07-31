/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax+list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:49:39 by khanhayf          #+#    #+#             */
/*   Updated: 2023/07/31 09:36:31 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i])
	{
		if (ft_strchr("\"\'", s[i]))
		{
			c = s[i];
			if (doubles(&s[i]))
				return (1);
			i++;
			while (s[i] && s[i] != c)
				i++;
		}
		if ((s[i] == '>' && s[i + 1] == '>')
			|| (s[i] == '<' && s[i + 1] == '<'))
			i++;
		if (check_others(s, i))
			return (1);
		i++;
	}
	return (0);
}

char	*get_type1(char *s, char *str)
{
	int	j;

	if (s[0] == '<' && s[1] != '<')
		return ("infile\0");
	else if (s[0] == '<' && s[1] == '<')
		return ("h_doc\0");
	else if (s[0] == '>' && s[1] != '>')
		return ("o_file\0");
	else if (s[0] == '>' && s[1] == '>')
		return ("append\0");
	else if ((s[0] == '$' || s[0] == '\"'))
	{
		if (s[0] == '\"')
		{
			j = 0;
			while (s[j] && s[j] != '$')
				j++;
			if (s[j] && s[j] == '$' && (ft_memcmp (str, "h_doc\0", 5)))
				return ("env\0");
		}
		else if (s[0] == '$' && (ft_memcmp (str, "h_doc\0", 5)))
			return ("env\0");
	}
	return (NULL);
}

char	*get_type(char *s, int n, char *str)
{
	char	*p;

	if (n == 0 && !ft_strchr(">|<", s[0]))
		return ("cmd\0");
	if (n > 0 && !(ft_memcmp(str, "h_doc\0", 6)))
		return ("del\0");
	p = get_type1(s, str);
	if (p)
		return (p);
	if (s[0] == '|')
		return ("pipe\0");
	else if (n > 0 && (!(ft_memcmp(str, "infile\0", 7))
			|| !(ft_memcmp(str, "o_file\0", 7))
			|| !(ft_memcmp(str, "append\0", 6))))
		return ("file\0");
	if (s[0] == '-' || (ft_memcmp (str, "pipe\0", 5)))
		return ("opt\0");
	else if (ft_memcmp (str, "cmd\0", 4))
		return ("cmd\0");
	return (NULL);
}
