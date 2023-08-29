/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:26:46 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/14 16:07:41 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *str, int c)
{
	char	*p;
	int		i;

	p = (char *)str;
	i = 0;
	while (p[i])
	{
		if (p[i] == (char)c)
			return (&p[i]);
		i++;
	}
	if (p[i] == (char)c)
		return (&p[i]);
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, int n)
{
	char	*d;
	char	*s;
	int		i;

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	if (src == NULL && dest == NULL)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void	release(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free (tab);
}

int	ft_strlen(char *s)
{
	int		i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_memcmp(char *p1, char *p2, int s)
{
	int		l1;
	int		l2;

	if (s == 0)
		return (0);
	l1 = ft_strlen(p1);
	l2 = ft_strlen(p2);
	if (l1 >= l2)
		s = l1;
	else
		s = l2;
	while (s > 1)
	{
		if (*p1 == *p2)
		{
			p1++;
			p2++;
		}
		s--;
	}
	return (*p1 - *p2);
}
