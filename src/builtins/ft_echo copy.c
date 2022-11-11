/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   echo.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: emlicame <emlicame@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/10/06 15:23:51 by emlicame		  #+#	#+#			 */
/*   Updated: 2022/10/22 18:31:35 by emlicame		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../execution_src/execution.h"

void	ft_putstr_fd(char *s, int fd);

int	check_if_n(char *str)
{
	int	i;
	int	nl;

	i = 0;
	nl = 0;
	while (str[i])
	{
		if (str[i] == '-')
		{
			i++;
			if (str[i] == 'n')
				nl = 1;
		}
		i++;
	}
	return (nl);
}

void	print_echo(char **arg, int i, int *is_nl)
{
	while (arg[i] != NULL)
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i] + 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (*is_nl == 0)
		ft_putstr_fd("\n", 1);
}
//
//if no text after  -n SEGV
// echo - hello

int	ft_echo(char **arg)
{
	int		i;
	int		is_n;

	i = 0;
	is_n = 0;
	while (arg[i++] && arg[i][0] == '-')
	{
		if (check_if_n(arg[i]) == 1)
			is_n = 1;
		else
			break ;
	}
	print_echo(arg, i, &is_n);
	return (0);
}
