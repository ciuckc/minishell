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

static void	st_cmd_input(t_table *env_table)
{
	char		*full_cmd;
	t_cmd_list	*cmd_list;

	(void)env_table;
	cmd_list = NULL;
	full_cmd = NULL;
	while (true)
	{
		full_cmd = readline("\033[1;32mminishell$\033[0m ");
		cmd_list = parser(full_cmd);
		if (cmd_list == NULL)
		{
			free(full_cmd);
			continue ;
		}
		//expand_variables(cmd_list->cmd_list, env_table);
		free(full_cmd);
	}
}

static void	st_one_cmd(char *argv, t_table *env_table)
{
	t_cmd_list	*cmd_list;

	(void)env_table;
	cmd_list = parser(argv);
	if (cmd_list == NULL)
		return ;
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	t_table	*env_table;

	env_table = create_env_table(envp);
	if (env_table == NULL)
		return (EXIT_FAILURE);
	if (argc == 1)
		st_cmd_input(env_table);
	else if (argc == 2)
		st_one_cmd(*(argv + 1), env_table);
	return (EXIT_SUCCESS);
}
