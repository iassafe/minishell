/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:42:12 by khanhayf          #+#    #+#             */
/*   Updated: 2023/08/19 16:13:49 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isalnum(char c)
{
	if ((c >= 97 && c <= 122)
		|| (c >= 65 && c <= 90) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}

char	*ft_substr(char *s, int first, int len)
{
	char	*sub;
	int		i;
	int		l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (len > l)
		len = l;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	ft_alloc(sub);
	i = 0;
	while (*s && i < len && first <= l)
		sub[i++] = s[first++];
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		l1;
	int		l2;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s1)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!p)
		return (0);
	ft_alloc(p);
	ft_memcpy(p, s1, l1);
	ft_memcpy(p + l1, s2, l2 + 1);
	return (p);
}

void	ft_putstr(char *s, int fd)
{
	int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
		write (fd, &s[i++], 1);
}
