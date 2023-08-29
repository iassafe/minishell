/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:52:42 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/19 13:14:54 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_exit(char *str)
{
	ft_putstr("exit\n", 2);
	ft_putstr("minishell: exit: ", 2);
	ft_putstr(str, 2);
	ft_putstr(": numeric argument required\n", 2);
	g_gl.exit = 255;
	exit(255);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	check_c(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		print_error_exit(str);
	while (str[i])
	{
		if ((str[i] == '+' || str[i] == '-'))
		{
			if (!ft_isdigit(str[i + 1]))
				print_error_exit(str);
			else
				i++;
		}
		else if (!ft_isdigit(str[i]))
			print_error_exit(str);
		i++;
	}
}

long	ft_atoi_check(char *str)
{
	int					i;
	int					s;
	unsigned long long	n;

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
	check_c(str);
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i++] - 48;
		if ((n > LLONG_MAX && s == 1) || ((n - 1) > LLONG_MAX && s == -1))
			print_error_exit(str);
	}
	return (s * n);
}

void	check_arg(t_exec *x)
{
	int				i;
	long long		nb;

	i = 1;
	nb = 0;
	while (x->cmd[i])
	{
		nb = ft_atoi_check(x->cmd[i]);
		if (!x->cmd[i + 1])
		{
			ft_putstr("exit\n", 2);
			g_gl.exit = nb;
			exit(nb);
		}
		else if (x->cmd[i + 1])
		{
			ft_putstr("exit\n", 2);
			ft_putstr("minishell: exit: too many arguments\n", 2);
			g_gl.exit = 1;
			return ;
		}
		i++;
	}
}
