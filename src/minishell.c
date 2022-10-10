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

static void	st_cmd_input(char **envp)
{
	char	*full_cmd;

	full_cmd = NULL;
	while (true)
	{
		full_cmd = readline("$ ");
		parser(full_cmd, envp);
		free(full_cmd);
	}
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	if (argc == 1)
	{
		st_cmd_input(envp);
	}
	else if (argc == 2)
	{
		parser(*argv, envp);
	}
	return (0);
}
