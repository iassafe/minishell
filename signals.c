/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:36:08 by iassafe           #+#    #+#             */
/*   Updated: 2023/08/17 16:43:35 by iassafe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(void)
{
	printf("exit\n");
	g_gl.exit = 0;
	exit(0);
}

void	sig_herdoc(int signum)
{
	g_gl.ctrl_c = 1;
	(void)signum;
	close(0);
}

void	quit_herdoc(char *line, int fd)
{
	if (!line)
	{
		if (g_gl.ctrl_c == 1)
		{
			dup2(fd, 0);
			close(fd);
		}
	}
}

void	sigint_handler(int si)
{
	int	status;

	(void)si;
	if (waitpid(-1, 0, WNOHANG) == 0)
		return ;
	if (WIFSIGNALED(status))
		g_gl.exit = WIFSIGNALED(status);
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	signals_handler(int status)
{
	if (WIFEXITED(status))
		g_gl.exit = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3 || WTERMSIG(status) == 2)
		{
			g_gl.exit = WTERMSIG(status) + 128;
			if (WTERMSIG(status) == 3)
				printf("Quit: %d\n", WTERMSIG(status));
			else
				printf("\n");
		}
	}
}
