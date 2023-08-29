/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulist_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 08:05:11 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/17 17:57:50 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_list_env(void *list)
{
	if (!g_gl.f_env)
	{
		g_gl.f_env = malloc(sizeof(t_free));
		if (!g_gl.f_env)
			return ;
		g_gl.f_env->ptr = list;
		g_gl.f_env->link = NULL;
	}
	else
		ft_alloc_env(list);
}

void	ft_alloc_env(void *p)
{
	t_free_env	*next;
	t_free_env	*new;

	next = g_gl.f_env;
	new = NULL;
	while (next->link)
		next = next->link;
	new = malloc(sizeof(t_free));
	if (!new)
		return ;
	new->ptr = p;
	new->link = NULL;
	next->link = new;
}

void	free_list_env(void)
{
	t_free_env	*next;

	while (g_gl.f_env)
	{
		free (g_gl.f_env->ptr);
		next = g_gl.f_env->link;
		free(g_gl.f_env);
		g_gl.f_env = next;
	}
}

char	*ft_substr1(char *s, int first, int len)
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
	alloc_list_env(sub);
	i = 0;
	while (*s && i < len && first <= l)
		sub[i++] = s[first++];
	sub[i] = '\0';
	return (sub);
}

char	*ft_itoa1(int n)
{
	int		len;
	char	*str;
	long	nb;

	len = ft_nb_len(n);
	nb = n;
	str = malloc(sizeof(char) * len + 1);
	if (! str)
		return (NULL);
	alloc_list_env(str);
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (nb)
	{
		str[len--] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}
