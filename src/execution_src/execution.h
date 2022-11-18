/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:00:13 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/17 19:49:28 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/errno.h>

# define READ 0
# define WRITE 1

typedef struct s_input
{
	char			**environ;
	char			**paths;
	char			*cmd_path;
	char			**cmd_args;
	int				exit_for_pipe;
	int				cmd_count;
	int				exit_code;
	int				temp_fd[2];
	int				fds[2];
	int				readfd;
	int				pipe_fd[2];
}	t_input;

void		get_path(t_input *data);
void		error_exit(char *text, int exit_code);
// void		error_print(char *text);
void		command_not_found(t_input *data);
void		permission_denied(t_input *data);
void		no_such_file(t_input *data);
void		get_cmd(t_token *tok, t_input *data);
void		count_cmds(t_token *tok, t_input *data);
int			access_file(t_input *data);
int			open_infiles(t_token *tok, t_input *data);
int			open_outfiles(t_token *tok, t_input *data);
int32_t		dup_and_close(int fd, int in_out);
int			exec_single(t_token *tok, t_input *data);
int			single_command(t_token *tok, t_input *data);
int			multiple_commands(t_token *tok, t_input *data);
void		child_process(t_token *tok, t_input *data, int max);
int			waiting(int id, int max);

void		get_env_array(char **envi, t_input *data);

/**built-ins **/
int			run_builtin(t_input *data);
bool		is_built_in(char *cmd);
int			ft_echo(char **arg);
int			ft_cd(t_input *data);
int			ft_pwd(t_input *data);
// int			ft_exit(char **arg);
int			ft_exit(t_input *data);

/*utils*/
char		*ft_strjoin_withfree(char *s1, char *s2);

#endif