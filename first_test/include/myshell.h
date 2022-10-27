/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:00:13 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/25 14:38:36 by emlicame         ###   ########.fr       */
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

enum e_token_type
{
	WORD,
	GRT_TH,
	SMLR_TH,
	DGRT_TH,
	DSML_TH,
	EMPTY,
	PIPE,
};

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
	char			**cmd_args;
	char			*cmd_path;
	int				fds[3];
}	t_input;

typedef struct s_token
{
	char			*content;
	int				token_type;
	struct s_token	*next;
}	t_token;

// typedef struct a
// {
// 	t_token t;
// 	t_envi e;
// 	t_input i;
// } aa;

t_envi	*env_init(char **envi);
void	list_clear(t_envi **lst);
t_envi	*ft_lstnew(void *content);
t_envi	*ft_lstlast(t_envi *lst);
void	ft_lstadd_back(t_envi **lst, t_envi *new);
void	ft_lstadd_back_t(t_token **lst, t_token *new);
t_token	*argv_init(char **args);
t_token	*get_test_input(void);

t_token	*ft_lstnew_t(void *content);
t_token	*ft_lstlast_t(t_token *lst);
void	list_clear_t(t_token **lst);
int		ft_lstsize(t_token *lst);

int		exec_cmd(t_envi **envi, t_token **tok, t_input **data);
void	get_path(t_envi *envi, t_input *data);
void	error_exit(char *text, int exit_code);
void	get_arg_path(t_input *var, int i);
void	get_cmd(t_token **tok, t_input *data);
void	execution(t_token *tok, t_input *data);
int		access_file(t_input **data);
void	dupfiles(t_input *data);
int		check_builtin(t_token **tok, t_input *data);

int		ft_echo(char **arg);
int		ft_cd(t_input *data);

char	**ft_split(char const *s, char c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin_withfree(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);

#endif