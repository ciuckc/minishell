/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_tmp_file_here.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/12 06:28:12 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/15 18:02:06 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../execution_src/execution.h"

static void	self_pid(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	g_exit_code = info->si_pid;
}

static pid_t	st_get_pid(void)
{
	u_int64_t			exit_temp;
	struct sigaction	sig_act;
	pid_t				my_pid;

	exit_temp = g_exit_code;
	sig_act.sa_flags = SA_SIGINFO;
	sig_act.sa_sigaction = self_pid;
	sigaction(SIGUSR1, &sig_act, NULL);
	kill(0, SIGUSR1);
	my_pid = g_exit_code;
	g_exit_code = exit_temp;
	return (my_pid);
}

static char	*st_create_id(t_token *id_ptr)
{
	uint64_t		my_pid;
	static uint64_t	id;
	char			*id_str;

	my_pid = st_get_pid();
	id = (uint64_t)id_ptr ^ (my_pid << 32) ^ (id << 40);
	id ^= FNV_PRIME;
	id_str = ft_ultoa(id);
	if (id_str == NULL)
		return (NULL);
	return (id_str);
}

static char	*st_create_file_name(t_token *id_ptr)
{
	char	*file_name;
	char	*id_str;

	id_str = st_create_id(id_ptr);
	if (id_str == NULL)
		return (NULL);
	file_name = ft_strjoin("/tmp/.here_", id_str);
	if (file_name == NULL)
		return (free(id_str), NULL);
	return (free(id_str), file_name);
}

int32_t	create_tmp_file_here(char **str, t_token *id_ptr)
{
	int32_t			fd;

	*str = st_create_file_name(id_ptr);
	if (*str == NULL)
		return (-1);
	fd = open(*str, O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0777);
	if (fd == -1)
	{
		free(*str);
		*str = NULL;
		return (-1);
	}
	return (fd);
}
