/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_sig_handle.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 07:02:55 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/21 14:46:25 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

static void	st_handle_interrupt(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	g_exit_code += signum + 128;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	init_sig_handle(void)
{
	struct sigaction	sig_inter;

	sig_inter.sa_flags = SA_SIGINFO;
	sig_inter.sa_sigaction = st_handle_interrupt;
	sigaction(SIGINT, &sig_inter, NULL);
	signal(SIGQUIT, SIG_IGN);
}
