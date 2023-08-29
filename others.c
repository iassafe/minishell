/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:21:14 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/19 16:32:32 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(char	*cmd)
{
	if (cmd)
	{
		if ((!ft_memcmp(cmd, "echo", 5))
			|| (!ft_memcmp(cmd, "pwd", 4))
			|| (!ft_memcmp(cmd, "env", 4))
			|| (!ft_memcmp(cmd, "export", 7))
			|| (!ft_memcmp(cmd, "unset", 6))
			|| (!ft_memcmp(cmd, "cd", 3))
			|| (!ft_memcmp(cmd, "exit", 4)))
			return (1);
	}
	return (0);
}

int	check_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	check_dir(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == '.' || cmd[i] == '/')
		i++;
	if (cmd[i] == '\0' && i)
		return (1);
	return (0);
}
