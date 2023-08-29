/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:11:23 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/19 15:02:38 by iassafe          ###   ########.fr       */
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
	if (src == NULL)
		return (NULL);
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

int	ft_atoi(const char *str)
{
	int		i;
	int		s;
	int		n;

	n = 0;
	s = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i++] - 48;
	}
	return (s * n);
}
