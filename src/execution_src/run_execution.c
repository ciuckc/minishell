/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: emlicame <emlicame@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/10/10 13:56:04 by emlicame		  #+#	#+#			 */
/*   Updated: 2022/10/19 14:03:27 by emlicame		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "execution.h"

int	run_execution(char **argv, char **envp)
{
	t_envi		*envi_head;
	t_input		*args;
	t_token		*input;

	(void)argv;
	envi_head = env_init(envp);
	input = get_test_input();
	args = (t_input *)malloc(sizeof(t_input) * 1);
	args->paths = (char **)malloc(sizeof (char *) * 1);
	args->paths = NULL;
	args->environ = envp;
	data_fetch(&envi_head, &input, &args);
	return (0);
}

	// t_token		*tok;
	// tok = argv_init(argv);

	// aa superstruct;
/*

int	main(int argc, char **argv, char **envp)
{
	t_envi		*envi_head;
	t_input		*args;
	t_token		*tok;

	(void)argc;
	envi_head = env_init(envp);
	tok = argv_init(argv);
	args = (t_input *)malloc(sizeof(t_input) * 1);
	args->paths = (char **)malloc(sizeof (char *) * 1);
	args->paths = NULL;
	args->environ = envp;
	exec_cmd(&envi_head, &tok, &args);
	return (0);
}
*/