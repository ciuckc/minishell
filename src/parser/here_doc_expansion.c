/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc_expansion.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 19:26:12 by scristia      #+#    #+#                 */
/*   Updated: 2022/12/15 18:33:40 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../expansion/var_expansion.h"
#include "../utils/libft/libft.h"
#include "../execution_src/execution.h"

static void	st_uncouple_nodes(t_token **word, char *file_name)
{
	t_token	*delim;
	t_token	*delim_next;
	t_token	*dless;

	delim = *word;
	delim_next = (*word)->next;
	dless = (*word)->prev;
	if (delim_next)
		delim_next = dless;
	if (dless)
		dless->next = delim_next;
	free(delim->str);
	free(delim);
	free(dless->str);
	dless->str = file_name;
	*word = dless;
}

static void	st_read_here(t_token **delim, int32_t fd)
{
	char		*read_line;

	init_sig_handle(3);
	while (true)
	{
		read_line = readline("> ");
		if (read_line == NULL)
			exit (1);
		if (!ft_strcmp(read_line, (*delim)->str))
			break ;
		ft_putendl_fd(read_line, fd);
		free(read_line);
	}
	free(read_line);
	exit (0);
}

static void	st_if_type_is_dless(t_cmd_list **cmd, u_int32_t i)
{
	pid_t	child_pid;
	char	*file_name;
	int32_t	fd;

	child_pid = -1;
	file_name = NULL;
	fd = -1;
	if ((*cmd)[i].cmd_list->type == DLESS)
	{
		(*cmd)[i].cmd_list = (*cmd)[i].cmd_list->next;
		remove_quotes((*cmd)[i].cmd_list);
		fd = create_tmp_file_here(&file_name, (*cmd)[i].cmd_list);
		if (fd == -1)
			error_exit("file descriptor failed", 1);
		child_pid = fork();
		if (child_pid == -1)
			error_exit("fork failed", 1);
		if (child_pid == 0)
			st_read_here(&(*cmd)[i].cmd_list, fd);
		waiting(child_pid, 1);
		close(fd);
		st_uncouple_nodes(&(*cmd)[i].cmd_list, file_name);
	}
}

static void	st_count_here_docs(t_cmd_list **cmd)
{
	t_token		*head;
	u_int32_t	i;
	u_int32_t	here_doc_count;

	head = NULL;
	i = 0;
	here_doc_count = 0;
	while ((*cmd)[i].cmd_list)
	{
		head = (*cmd)[i].cmd_list;
		while ((*cmd)[i].cmd_list)
		{
			if ((*cmd)[i].cmd_list->type == DLESS)
				here_doc_count++;
			(*cmd)[i].cmd_list = (*cmd)[i].cmd_list->next;
		}
		(*cmd)[i].cmd_list = head;
		i++;
	}
	if (here_doc_count > 15)
	{
		free_cmd_list(cmd);
		error_exit("maximum here-document count exceeded", 2);
	}
}

void	here_doc_expansion(t_cmd_list **cmd)
{
	t_token		*head;
	u_int32_t	i;

	i = 0;
	head = NULL;
	st_count_here_docs(cmd);
	while ((*cmd)[i].cmd_list)
	{
		head = (*cmd)[i].cmd_list;
		while ((*cmd)[i].cmd_list)
		{
			st_if_type_is_dless(cmd, i);
			if ((*cmd)[i].cmd_list->str == NULL)
				return (free_cmd_list(cmd));
			(*cmd)[i].cmd_list = (*cmd)[i].cmd_list->next;
		}
		(*cmd)[i].cmd_list = head;
		i++;
	}
	here_doc_node_remove(cmd);
	init_sig_handle(1);
}
