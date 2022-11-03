/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:00:13 by emlicame          #+#    #+#             */
/*   Updated: 2022/11/03 17:24:42 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <sys/errno.h>

# define READ 0
# define WRITE 1

typedef enum e_token_type
{
	WORD = 1,
	ASSIGNMENT_WORD = 1 << 1,
	PIPE = 1 << 2,
	LESS = 1 << 3,
	GREAT = 1 << 4,
	DLESS = 1 << 5,
	DGREAT = 1 << 6,
	AND_IF = 1 << 7,
	OR_IF = 1 << 8,
	S_QUOTE = 1 << 9,
	D_QUOTE = 1 << 10,
	END = 1 << 11
}	t_token_type;

typedef struct s_envi
{
	char			*envectors;
	struct s_envi	*next;
}	t_envi;

typedef struct s_input
{
	char			**environ;
	char			**paths;
	char			*cmd_path;
	char			**cmd_args;
	char			**cmds;
	char			**infile;
	char			**outfile;
	int				cmd_count;
	int				readfd;
	int				fds[2];
	int				pipe_fd[2];
	int				temp_fd[2];
	struct s_file	*file_lst;
}	t_input;

typedef struct s_file
{
	char			*name;
	t_token_type	flag;
	struct s_file	*next;
}	t_file;

typedef struct s_token
{
	char			*content;
	t_token_type	token_type;
	struct s_token	*next;
}	t_token;

// typedef struct a
// {
// 	t_token t;
// 	t_envi e;
// 	t_input i;
// } aa;

int			run_execution(char **argv, char **envp);
int			data_fetch(t_token **tok, t_input **data);
void		get_path(t_input *data);
void		error_exit(char *text, int exit_code);
void		get_cmd(t_token *tok, t_input *data);
void		execution(t_input *data);
int			access_file(t_input *data);
void		dupfiles(t_input *data);
int			check_builtin(t_input *data);
bool		is_built_in(char *cmd);
int			single_command(t_token *tok, t_input *data);
void		execution_start(t_token *tok, t_input *data);
void		openfiles(t_token *tok, t_input *data);
int			exec_single(t_token *tok, t_input *data);
int			multiple_commands(t_token *tok, t_input *data);
void		count_cmds(t_token *tok, t_input *data);
void		set_fds(t_input *data);

int			ft_echo(char **arg);
int			ft_cd(t_input *data);

/*for lists - exec_utils*/
t_token		*get_test_input(void);
void		ft_lstadd_back_t(t_token **lst, t_token *new);
t_token		*ft_lstnew_t(void *content);
t_token		*ft_lstlast_t(t_token *lst);
int			ft_lstsize_t(t_token *lst);
void		get_files_input(t_token *tok, t_input *data);
void		get_env_array(char **envi, t_input **data);

/*utils*/
char		*ft_strjoin_withfree(char *s1, char *s2);

/*from libft*/
char		**ft_split(char const *s, char c);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strdup(const char *s1);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *s, int fd);

#endif