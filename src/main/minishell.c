/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 21:54:47 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/16 20:56:43 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "main.h"

u_int64_t volatile	g_exit_code = 0;

static void	st_cmd_input(t_table *env_table, char ***envp)
{
	char		*full_cmd;
	t_cmd_list	*cmd_list;

	while (true)
	{
		init_sig_handle(0);
		full_cmd = readline(PROMPT);
		if (!full_cmd)
		{
			write(1, "exit\n", 6);
			return ;
		}
		cmd_list = parser(full_cmd, env_table);
		if (cmd_list == NULL)
		{
			free(full_cmd);
			continue ;
		}
		execute_loop(&cmd_list, env_table, envp);
		free(full_cmd);
	}
}

static void	st_one_cmd(char *argv, t_table *env_table, char ***envp)
{
	t_cmd_list	*cmd_list;

	cmd_list = parser(argv, env_table);
	if (cmd_list == NULL)
		return ;
	execute_loop(&cmd_list, env_table, envp);
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_table	*env_table;

	env_table = create_env_table(envp);
	init_sig_handle(0);
	rl_outstream = stderr;
	if (env_table == NULL)
		return (EXIT_FAILURE);
	if (argc == 1)
		st_cmd_input(env_table, &envp);
	else if (argc == 2)
		st_one_cmd(*(argv + 1), env_table, &envp);
	clear_history();
	remove_all(env_table);
	return (g_exit_code);
}
