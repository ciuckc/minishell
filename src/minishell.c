/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 21:54:47 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/05 18:41:29by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_int64_t	g_exit_code = 0;

static void	st_execute_loop(t_cmd_list **cmd_list, t_table *env_table, \
char **envp)
{
	u_int32_t	i;
	char		**envp_head;

	envp_head = envp;
	i = 0;
	while ((*cmd_list)[i].cmd_list)
	{
		create_new_envp(env_table, &envp);
		expand_words(cmd_list[i]->cmd_list, env_table);
		g_exit_code = execution((*cmd_list)[i].cmd_list, env_table, envp_head);
		if (g_exit_code != 0 && (*cmd_list)[i].cmd_list_type == AND_IF)
			break ;
		i++;
	}
}

static void	st_cmd_input(t_table *env_table, char **envp)
{
	char		*full_cmd;
	t_cmd_list	*cmd_list;

	cmd_list = NULL;
	full_cmd = NULL;
	while (true)
	{
		full_cmd = readline("\001\033[1;32m\002minishell$\001\033[0m\002 ");
		if (!full_cmd)
			exit(g_exit_code);
		cmd_list = parser(full_cmd);
		if (cmd_list == NULL)
		{
			free(full_cmd);
			continue ;
		}
		st_execute_loop(&cmd_list, env_table, envp);
		free(full_cmd);
	}
}

static void	st_one_cmd(char *argv, t_table *env_table, char **envp)
{
	t_cmd_list	*cmd_list;

	(void)env_table;
	cmd_list = parser(argv);
	if (cmd_list == NULL)
		return ;
	st_execute_loop(&cmd_list, env_table, envp);
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_table	*env_table;

	env_table = create_env_table(envp);
	init_sig_handle();
	rl_outstream = stderr;
	if (env_table == NULL)
		return (EXIT_FAILURE);
	if (argc == 1)
		st_cmd_input(env_table, envp);
	else if (argc == 2)
		st_one_cmd(*(argv + 1), env_table, envp);
	return (g_exit_code);
}
