/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_self_pid.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/10 20:45:14 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/10 21:04:04 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	st_get_pid(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	g_exit_code = info->si_pid;
	(void)context;
}

int32_t	get_self_pid(void)
{
	struct sigaction	sig_act;
	u_int64_t			exit_temp;
	pid_t				my_pid;

	sig_act.sa_flags = SA_SIGINFO;
	sigemptyset(&sig_act.sa_mask);
	sig_act.sa_sigaction = st_get_pid;
	exit_temp = g_exit_code;
	sigaction(SIGUSR1, &sig_act, NULL);
	kill(0, SIGUSR1);
	my_pid = g_exit_code;
	g_exit_code = exit_temp;
	signal(SIGUSR1, SIG_DFL);
	return (my_pid);
}
