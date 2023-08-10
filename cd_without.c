/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_without.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:14:18 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/10 09:21:58 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	without_home(char *home)
{
	if (!home)
	{
		ft_putstr("minishell: cd: HOME not set\n", 2);
	}
	else if (home && home[0] != '\0')
	{
		ft_putstr("minishell: cd: ", 2);
		ft_putstr(home, 2);
		ft_putstr(": No such file or directory\n", 2);
	}
}

void	with_home(char *home, char *pwd)
{
	t_env	*env;

	env = g_gl.env;
	while (env)
	{
		if (!ft_memcmp("OLDPWD", env->var, ft_strlen(env->var) + 7))
			env->value = pwd;
		else if (!ft_memcmp("PWD", env->var, ft_strlen(env->var) + 4))
			env->value = home;
		env = env->link;
	}
}

void	cd_without(void)
{
	t_env	*env;
	char	*pwd;
	char	*home;

	env = g_gl.env;
	home = NULL;
	pwd = NULL;
	while (env)
	{
		if (!ft_memcmp(env->var, "PWD", ft_strlen(env->var) + 4))
		{
			if (env->value)
				pwd = ft_strdup(env->value);
		}
		else if (!ft_memcmp(env->var, "HOME", ft_strlen(env->var) + 5))
		{
			if (env->value)
				home = ft_strdup(env->value);
		}
		env = env->link;
	}
	if (chdir(home) == 0)
		with_home(home, pwd);
	else
		without_home(home);
}

void	xec_cd(t_exec *x)
{
	if (!x->cmd[1] || (x->cmd[1] && x->cmd[1][0] == '\0' && x->quo == 0))
		cd_without();
	else if (x->cmd[1] && x->cmd[1][0] != '\0')
		cd_with(x->cmd[1]);
}
