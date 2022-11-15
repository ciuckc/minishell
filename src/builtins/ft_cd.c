/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:35 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/15 18:37:30 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution_src/execution.h"

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
}
