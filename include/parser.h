#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"
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

// For command execution (used by executor)
typedef struct s_cmd
{
	int				in_file;
	int				out_file;
	char			**full_cmd;
	int				access;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;


// Env list
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

// Export list (if needed by builtins)
typedef struct s_export
{
	char			*name;
	char			sep;
	char			*value;
	struct s_export	*next;
}	t_export;

typedef struct s_expand_data
{
	char		**res;
	int			*len;
	int			*max;
	int			exit_code;
}				t_expand_data;

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

// Full parser data object
typedef struct s_data
{
	t_cmd			*head;
	char			*input;
	t_list			*cmd_lst;
	int				in;
	int				out;
	t_elem			*elem;
	int				exit_status;
	int				error;
	int				file_error;
	int				expanded;
	char			*expnd;
	t_list			*save_error;
	struct s_env	*n_env;
}	t_data;

#endif