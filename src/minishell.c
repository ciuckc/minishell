/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 21:54:47 by scristia      #+#    #+#                 */
/*   Updated: 2022/09/30 17:18:50 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	main(int32_t argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	if (argc == 1)
	{
		readline("minishell%% ");
		parser(*argv);
		return (0);
	}
	else if (argc == 2)
	{
		parser(*argv);
	}
	return (0);
}
