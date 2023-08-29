/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_with.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:41:10 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/19 16:13:08 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(char *pwd)
{
	t_env	*env;

	env = g_gl.env;
	while (env)
	{
		if (!ft_memcmp("OLDPWD", env->var, ft_strlen(env->var) + 7))
			env->value = pwd;
		else if (!ft_memcmp("PWD", env->var, ft_strlen(env->var) + 4))
			env->value = g_gl.pwd;
		env = env->link;
	}
}

void	print_error(void)
{
	ft_putstr("chdir: error retrieving current directory: getcwd: ", 2);
	ft_putstr("cannot access parent directories: ", 2);
	ft_putstr("No such file or directory\n", 2);
}

void	error_dir(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		ft_putstr("minishell: cd: ", 2);
		ft_putstr(cmd, 2);
		ft_putstr(": Not a directory\n", 2);
	}
	else
	{
		ft_putstr("minishell: cd: ", 2);
		ft_putstr(cmd, 2);
		ft_putstr(": No such file or directory\n", 2);
	}
	g_gl.exit = 1;
}

void	cd_with(char *cmd)
{
	char	*pwd;
	t_env	*env;

	env = g_gl.env;
	pwd = NULL;
	while (env)
	{
		if (!ft_memcmp(env->var, "PWD", ft_strlen(env->var) + 4))
		{
			if (env->value)
				pwd = env->value;
			break ;
		}
		env = env->link;
	}
	if (!chdir(cmd))
	{
		if (cmd[0] == '.' && !getcwd(g_gl.pwd, sizeof(g_gl.pwd)))
			print_error();
		change_dir(pwd);
		g_gl.exit = 0;
	}
	else
		error_dir(cmd);
}
