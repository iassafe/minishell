/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:19:37 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/19 16:14:05 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlcpy(char *dst, char *src, int dsize)
{
	int	i;
	int	l;

	l = ft_strlen(src);
	if (dsize == 0)
		return (l);
	i = 0;
	while (src[i] && i < dsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (l);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*p;
	int		l1;
	int		l2;
	int		l3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	l3 = ft_strlen(s3);
	p = (char *)malloc(sizeof(char) * (l1 + l2 + l3 + 1));
	if (p == NULL)
		return (NULL);
	ft_alloc(p);
	ft_strlcpy(p, s1, l1 + 1);
	ft_strlcpy(p + l1, s2, l2 + 1);
	ft_strlcpy(p + (l1 + l2), s3, l3 + 1);
	return (p);
}

int	c_rows1(char const *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			n++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (n + 1);
}

char	**c_col1(char **tab, char *s, char c)
{
	char	*tmp;
	int		j;

	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			tmp = s;
			while (*s != c && *s)
				s++;
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
	tab[j] = 0;
	return (tab);
}

char	**fun_split(char *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * c_rows1(s, c));
	if (tab == NULL)
		return (NULL);
	ft_alloc(tab);
	tab = c_col1(tab, s, c);
	return (tab);
}
