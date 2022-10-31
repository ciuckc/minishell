/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiple_cmd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 16:34:34 by emlicame      #+#    #+#                 */
/*   Updated: 2022/10/30 12:00:04 by emanuela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	multiple_commands(t_input *data)
{
	int		exit_code;

	exit_code = 0;
	printf ("%s\n", data->cmd_path);
	return (exit_code);
}
