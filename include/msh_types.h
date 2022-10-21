/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_types.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 05:54:23 by scristia      #+#    #+#                 */
/*   Updated: 2022/10/21 03:03:06 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_TYPES_H
# define MSH_TYPES_H

# include <stddef.h>

# define OPERATORS "<>|&"
# define IFS " \t\n"
# define QUOTES "'\""
# define VAR_ASSIGN "$"

/*ENV VALUE STRUCT*/

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

/*TOKEN STRUCTS*/

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

typedef struct s_tok_len
{
	u_int32_t	start;
	u_int32_t	end;
}	t_tok_len;

typedef struct s_scan
{
	char			*orginal_str;
	t_tok_len		boundry;
	struct s_scan	*next;
	struct s_scan	*prev;
}	t_scan_tok;

typedef struct s_token
{
	char			*tok;
	t_token_type	type;
}	t_token;

typedef struct s_token_list
{
	t_token				*tok;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}	t_token_list;

#endif