/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
<<<<<<< HEAD:src/expansion/expand_var_in_str.c
/*   expand_var_in_str.c                                :+:    :+:            */
=======
/*   ft_cd.c                                            :+:    :+:            */
>>>>>>> execution:src/builtins/ft_cd.c
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
<<<<<<< HEAD:src/expansion/expand_var_in_str.c
/*   Created: 2022/11/08 04:02:53 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/09 16:04:55 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "var_expansion.h"

void	expand_var_in_str(t_token *word, t_table *table)
{
	ssize_t	sum_expanded_vars;

	(void)table;
	sum_expanded_vars = expanded_var_len(word->str, table);
=======
/*   Created: 2022/10/25 09:16:35 by emlicame      #+#    #+#                 */
/*   Updated: 2022/10/30 12:08:57 by emanuela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_cd(t_input *data)
{
	char	*path;
	char	*cwd;

	path = "/Users/emlicame";
	if (!data->cmd_args[1])
		data->cmd_args[1] = path;
	printf ("af path %s\n", data->cmd_args[1]);
	if (chdir(data->cmd_args[1]) == -1)
		error_exit("directory not found", 1);
	cwd = getcwd(NULL, 0);
	printf ("cwd = %s\n", cwd);
	//set environ variable(cwd)
	free (cwd);
	return (0);
>>>>>>> execution:src/builtins/ft_cd.c
}
