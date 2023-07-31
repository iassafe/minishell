/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:11:23 by iassafe           #+#    #+#             */
/*   Updated: 2023/07/31 11:16:10 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		write (2, &s[i++], 1);
	write (2, "\n", 1);
}

size_t	ft_nb_len(int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	nb;

	len = ft_nb_len(n);
	nb = n;
	str = malloc(sizeof(char) * len + 1);
	if (! str)
		return (NULL);
	ft_alloc(str);
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

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*t;

	i = 0;
	len = ft_strlen(src);
	t = (char *)malloc(sizeof(char) * (len + 1));
	if (!(t))
		return (NULL);
	ft_alloc(t);
	while (src[i])
	{
		t[i] = src[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
