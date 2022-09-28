
# Minishell
This project is about creating a simple shell.

## Build

Before anything run:
~~~
git submodule init
git submodule update
~~~
Now that the utilities are cloned, we can run:
~~~
make
~~~
## Minishell grammar

The following grammar defines the Shell Command Language. It is expressed via the Backus-Naur Form.

~~~
%token	WORD
%token	ASSIGNMENT_WORD
%token	NAME
%token	NEW_LINE

%token	DLESS 	'<<'
%token	DGREAT	'>>'

%token	AND_IF '&&'
%token	OR_IF '||'

%start complete_command

complete_command:	list	line_break
				|			line_break

list:	list	and_or
	|			and_or

and_or	:					pipeline
		|	and_or	AND_IF	pipeline
		|	and_or	OR_IF	pipeline

pipeline	:					command
			|	pipeline	'|'	command

command	:	cmd_prefix	cmd_word	cmd_suffix
		|	cmd_prefix	cmd_word
		|	cmd_prefix
		|	cmd_name	cmd_suffix
		|	cmd_name

cmd_name :	WORD	// Rule 7a: When the token is a reserved word, the token identifier for that reserved word, shall result. Otherwise the word shall be returned.
					//			Also, if the parser is in any state where only a reserved word could be the next correct token, proceed as above.
					//			Quoted strings cannot be recognized as reserved words.

cmd_word :	WORD	// Rule 7b:	If the token contains the equal sign character:
								->If it begins with '=', the token WORD shall be returned. EX: =word (error)
								->If all chararcters preceding '=' form a valid name, the token ASSIGNMENT_WORD shall be returned. (quoted chars cannot be there)
								->It it unspecified whether it is ASSIGNMENT_WORD or WORD that is returned.

cmd_prefix	:				io_file
			|	cmd_prefix	io_file
			|				ASSIGNMENT_WORD
			|	cmd_prefix	ASSIGNMENT_WORD

cmd_suffix	:				io_file
			|	cmd_suffix	io_file
			|				ASSIGNMENT_WORD
			|	cmd_suffix	ASSIGNMENT_WORD

io_file	:	'<'		filename
		|	'>'		filename
		|	DLESS	filename
		|	DGREAT	filename

filename :	WORD	//	Rule 2: The expansions specified in Redirection (see 2.7) shall occur.

line_break	:	NEW_LINE
~~~
