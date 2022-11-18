/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_sig_handle.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 07:02:55 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/18 21:24:39 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	st_handle_quit(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	g_exit_code = 0;
	ft_putstr_fd("exit\n", 1);
	exit(g_exit_code);
}

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
	struct sigaction	sig_quit;
	struct sigaction	sig_tstp;

	sig_inter.sa_flags = SA_SIGINFO;
	sig_quit.sa_flags = SA_SIGINFO;
	sig_tstp.sa_flags = SA_SIGINFO;
	sig_inter.sa_sigaction = st_handle_interrupt;
	sig_quit.sa_sigaction = st_handle_quit;
	sigaction(SIGINT, &sig_inter, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}
