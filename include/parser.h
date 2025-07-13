#ifndef PARSER_H
# define PARSER_H

#include "executor.h"
#include "../libft/libft.h"
/* ================================ ENUMS ================================ */

typedef enum e_type
{
	WORD = 1,
	WHITE_SPACE = ' ',
	QUOTE = '\'',
	DQUOTE = '\"',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	DREDIR_OUT,
	NEW_LINE = '\n',
	EXIT_STATUS,
	HERE_DOC,
	ESCAPE = '\\',
}	t_type;

typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL
}	t_state;

/* ============================== STRUCTS ================================ */

// Export list (if needed by builtins)
typedef struct s_export
{
	char			*name;
	char			sep;
	char			*value;
	struct s_export	*next;
}	t_export;


typedef struct s_lexer
{
	char	*input;
	int		len;
	int		position;
}			t_lexer;

// Token element (used inside parser)
typedef struct s_elem
{
	char			*content;
	t_type			type;
	t_state			state;
	struct s_elem	*next;
}	t_elem;


#endif