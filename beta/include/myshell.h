/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:00:13 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/27 19:45:40 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSHELL_H
# define MYSHELL_H

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
# define ERR 2

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
	char			**elements;
	char			**paths;
	char			*cmd_path;
	char			**cmd_args;
	char			**cmds;
	int				fds[2];
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

t_envi		*env_init(char **envi);
void		list_clear(t_envi **lst);
t_envi		*ft_lstnew(void *content);
t_envi		*ft_lstlast(t_envi *lst);
void		ft_lstadd_back(t_envi **lst, t_envi *new);
void		ft_lstadd_back_t(t_token **lst, t_token *new);
t_token		*argv_init(char **args);
t_token		*get_test_input(void);
t_token		*ft_lstnew_t(void *content);
t_token		*ft_lstlast_t(t_token *lst);
void		list_clear_t(t_token **lst);
int			ft_lstsize(t_token *lst);
t_file		*new_node_file(char *content, t_token_type flag);
t_file		*get_files_input(void);

int			data_fetch(t_envi **envi, t_token **tok, t_input **data);
void		get_path(t_envi *envi, t_input *data);
void		error_exit(char *text, int exit_code);
void		get_arg_path(t_input *var, int i);
void		get_cmd(t_token **tok, t_input *data);
void		execution(t_input *data);
int			access_file(t_input *data);
void		dupfiles(t_input *data);
int			check_builtin(t_input *data);
bool		is_built_in(char *cmd);
int			single_command(t_input *data);
void		execution_start(t_input *data);
void		get_files(t_input *data);
void		openfiles(t_input *data);
int			exec_single(t_input *data);
int			multiple_commands(t_input *data);

int			ft_echo(char **arg);
int			ft_cd(t_input *data);

char		**ft_split(char const *s, char c);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strdup(const char *s1);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strjoin_withfree(char *s1, char *s2);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *s, int fd);

#endif