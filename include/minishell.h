#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "builtins.h"
# include "executor.h"
# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include "signals.h"
# include "utils.h"

extern int					g_sigchild;

typedef enum perms
{
	NOT_AVAIL,
	NOT_EXEC,
	IS_A_DIR,
	IS_EXEC,
	CMD_NOT_FOUND,
	IS_BUILTIN,
	NULL_CMD,
}							t_perms;

typedef enum e_type t_type;

typedef struct s_token
{
	char					*value;
	t_type					type;
	struct s_token			*next;
}							t_token;

typedef struct s_redirection
{
	t_token					*redir;
	char					*arg;
	int						fd;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_expand
{
	char					*content;
	bool					should_split;
	bool					in_single_quotes;
	bool					in_double_quotes;
	struct s_expand			*next;
}							t_expand;

typedef struct s_alloc
{
	void					*allocated;
	struct s_alloc			*next;
}							t_alloc;

typedef struct s_parser
{
	char					*line;
	char					**result;
	char					*prompt;
	t_token					*head;
	t_cmd					*cmd;
	t_env					*env;
	t_expand				*expand;
	t_alloc					*alloc;
	int						exit_status;
	int						heredoc_abort;
}							t_parser;

typedef struct s_exec
{
	t_cmd			*cmds;
	t_env			*env;
	int				n_pipes;
	int				**pipes;
}							t_exec;

#endif
