/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_append_pid.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 23:09:00 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/30 18:16:35 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

static void	get_pid(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	g_exit_code = info->si_pid;
}

char	*str_append_pid(char *old_str, char *new_str, t_info *info)
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
		return (free(old_str), free(new_str), NULL);
	ft_memmove(new_str + info->j, str_pid, ft_strlen(str_pid));
	info->j += ft_strlen(str_pid);
	return (free(str_pid), new_str);
}
