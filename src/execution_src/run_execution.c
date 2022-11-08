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

int	data_fetch(t_token **tok, t_input **data)
{
	(*data)->fds[0] = 0;
	(*data)->fds[1] = 1;
	get_path(*data);
	get_cmd(*tok, *data);
	count_cmds(*tok, *data);
	execution_start(*tok, *data);
	return (0);
}

/// @brief 
/// @param envi 
/// @param data 
void	get_env_array(char **envi, t_input **data)
{
	int		i;
	char	**en;

	i = 0;
	while (envi[i])
		i++;
	en = (char **)malloc(sizeof(char *) * (i + 1));
	if (!en)
		error_exit("Malloc failed", 1);
	i = 0;
	while (envi[i])
	{
		en[i] = ft_strdup(envi[i]);
		i++;
	}
	en[i] = NULL;
	(*data)->environ = en;
}

/**
 * @brief this is test
 * @param argv from main
 * @param envp from main
 * @return some int value
*/
int	run_execution(char **argv, char **envp)
{
	t_input		*data;
	t_token		*input;

	(void)argv;
	input = get_test_input();
	data = (t_input *)malloc(sizeof(t_input) * 1);
	data->paths = (char **)malloc(sizeof (char *) * 1);
	if (!data->paths)
		error_exit("Malloc failed", 1);
	data->environ = envp;
	get_env_array(envp, &data);
	data_fetch(&input, &data);
	return (0);
}
