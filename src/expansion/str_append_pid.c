/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_append_pid.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 23:09:00 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/16 23:23:40 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

static void	get_pid(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	g_exit_code = info->si_pid;
}

void	str_append_pid(char **dst)
{
	struct sigaction	sig_act;
	u_int64_t			exit_temp;
	char				*str_pid;

	exit_temp = g_exit_code;
	sig_act.sa_flags = SA_SIGINFO;
	sig_act.sa_sigaction = get_pid;
	sigaction(SIGUSR1, &sig_act, NULL);
	kill(0, SIGUSR1);
	str_pid = ft_itoa(g_exit_code);
	g_exit_code = exit_temp;
	if (str_pid == NULL)
		return ;
	ft_memmove((*dst), str_pid, ft_strlen(str_pid));
	(*dst) += ft_strlen(str_pid);
	free(str_pid);
}
