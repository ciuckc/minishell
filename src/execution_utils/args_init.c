/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   args_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:13:20 by emlicame      #+#    #+#                 */
/*   Updated: 2022/10/30 12:36:20 by emanuela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_token	*argv_init(char **args)
{
	int		i;
	t_token	*argv_l;

	i = 0;
	argv_l = NULL;
	while (args[i])
		ft_lstadd_back_t(&argv_l, ft_lstnew_t(args[i++]));
	return (argv_l);
}

t_envi	*env_init(char **envi)
{
	int		i;
	t_envi	*envi_l;

	i = 0;
	envi_l = NULL;
	while (envi[i])
		ft_lstadd_back_e(&envi_l, ft_lstnew_e(envi[i++]));
	return (envi_l);
}
