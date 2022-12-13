/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sig_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 07:02:55 by scristia          #+#    #+#             */
/*   Updated: 2022/12/13 19:29:15 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

static void	st_handle_interrupt(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)signum;
	(void)context;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

static void	st_shell_env(void)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);
}

void	init_sig_handle(void)
{
	struct sigaction	sig_inter;

	st_shell_env();
	sig_inter.sa_flags = SA_SIGINFO;
	sig_inter.sa_sigaction = st_handle_interrupt;
	sigaction(SIGINT, &sig_inter, NULL);
	signal(SIGQUIT, SIG_IGN);
}
