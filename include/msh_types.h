/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_types.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 05:54:23 by scristia      #+#    #+#                 */
/*   Updated: 2022/11/09 18:12:44 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_TYPES_H
# define MSH_TYPES_H

# include <stddef.h>

# define OPERATORS "<>|&"
# define IFS " \t\n"
# define QUOTES "'\""
# define VAR_ASSIGN "$"

int	i;

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
	OR_IF = 1 << 3,
	AMP = 1 << 4,
	AND_IF = 1 << 5,
	LESS = 1 << 6,
	DLESS = 1 << 7,
	GREAT = 1 << 8,
	DGREAT = 1 << 9,
	S_QUOTE = 1 << 10,
	D_QUOTE = 1 << 11,
	DOLLAR = 1 << 12,
	END = 1 << 13
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

/*TOKEN LIST*/

/**
 * @brief 
 * 
 */
typedef struct s_token
{
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
	t_token_type	type;
}	t_token;

/*PARSE STRUCT LIST*/

typedef struct s_full_cmd_list
{
	t_token			*cmd_list;
	t_token_type	cmd_list_type;
}	t_cmd_list;

#endif