# ifndef EXECUTOR
#define EXECUTOR

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

extern int					g_sigchild;

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

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL
};

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

typedef struct s_token
{
	char					*value;
	t_type					type;
	struct s_token			*next;
}							t_token;

typedef struct s_expand_data
{
	char		**res;
	int			*len;
	int			*max;
	int			exit_code;
}				t_expand_data;

typedef struct s_cmd
{
	int				in_file;
	int				out_file;
	char			**full_cmd;
	int				access;
	pid_t			pid;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_elem
{
	char			*content;
	enum e_type		type;
	enum e_state	state;
	struct s_elem	*next;
}					t_elem;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_export
{
	char			*name;
	char			sep;
	char			*value;
	struct s_export	*next;
}					t_exprt;

typedef struct s_alloc
{
	void					*allocated;
	struct s_alloc			*next;
}							t_alloc;

typedef struct s_exec
{
	int			i;
	int			j;
	int			size;
	int			n_p;
	int			fork;
	int			**pe;
	char		*check;
	char		cd_path[1024];
	char		last_path[1024];
	char		old_path[1024];
	int			pos_path;
	char		**n_env;
	t_cmd		*tmp;
	t_env		*env;
	t_exprt		*export;
}				t_exec;

typedef struct s_data
{
	t_cmd			*head;
	char			*input;
	// t_list			*cmd_lst;
	int				in;
	int				out;
	t_elem			*elem;
	int				exit_status;
	int				error;
	int				file_error;
	int				expanded;
	char			*expnd;
	// t_list			*save_error;
	t_alloc			*alloc;
	struct s_env	*n_env;
}				t_data;

typedef struct s_parser
{
	char					*line;
	char					**result;
	char					*prompt;
	t_token					*head;
	t_cmd					*cmd;
	t_env					*env;
	t_expand_data				*expand;
	t_alloc					*alloc;
	int						exit_status;
	int						heredoc_abort;
}							t_parser;

				//builtins
int							ft_cd(t_cmd *cmd, pid_t pid, t_data *data);
void						ft_echo(t_cmd *cmd, pid_t pid, t_data *data);
int							ft_export(t_cmd *cmd, t_data *data);
void						ft_unset(t_cmd *cmd, pid_t pid, t_data *data);
int							ft_exit(t_cmd *cmd, pid_t pid, t_data *data);
void						ft_pwd(pid_t pid, t_data *data);
void						ft_env(t_env *env);
                //utils
		//free_utils
void						garbage_removal(t_alloc **alloc);
void						free_data(t_data *data);
void						ft_free(void *ptr, t_alloc **alloc);

int							check_for_child(pid_t pid, int exit_stat, t_data *data);
int							check_for_doubles(char *args);
char						*ft_strndup(const char *s, size_t n);
int							ft_strslen(char **strs);
int							ft_strcmp(char *s1, char *s2);
int							str_index(const char *str, int ch);
char						*ft_strjoin_free(char *s1, char *s2, int flag, t_data *data);
char						*get_value(char *key, t_env *env);
int							name_len(char *str);
char						*ft_strjoin_malloc(char *s1, char *s2, t_data *data);
char						*ft_strdup_alloc(const char *src, t_data *data);
char						*ft_substr_alloc(char const *s, unsigned int start, size_t len, t_data *data);
char						*ft_strdup_track(const char *s, int len, t_alloc **alloc);
int							args_check(t_cmd *cmd);
void						check_init(size_t *i, int *j, int *k, int *digit);
int							skip_whitespace(char *command, int i);
int							overflow_check(size_t test, int digit);
int							undeflow_check(size_t min_limit, size_t test, int digit, int last);
int							ft_isspace(char charac);
char						*get_valid_path(t_cmd *cmd, pid_t pid, t_data *data);
void						check_shlvl(t_env *env);
int							ft_atoi_shlvl(char *shlvl);
int							count_all_commands(t_cmd **cmds);
void						update_last_cmd(t_data *data);
int							count_char_array(char **commands);
int							*get_lastpid(void);
int							count_char_array(char **commands);
t_data						*get_data(void);
		//allocation_utils
void						*ft_malloc(size_t size, t_alloc **alloc);
void						add_alloc(void *allocated, t_alloc **alloc);
		//env_utils
t_env						*create_env_node(const char *env, t_data *data);
void						add_env_back(t_env **lst, t_env *new_node);
void						init_env_list(char **envp, t_data *data);
void						free_env_list(t_env *env);
t_env						*copy_env_list(t_env *env, t_data *data);
void						sort_env_list(t_env *env);
void						free_env(t_env *head, t_data *data);
int							env_name_exists(t_env *env, char *name);
void						edit_env(t_env *head, char *key, char *new_value);
void						add_env(t_env **head, char *key, char *value, t_data *data);
void						delete_env(t_env **env, char *key, t_data *data);
void						update_pwd(t_env *env, t_data *data);
void						env_update(t_env *env, t_data *data);
		//export_utils
void						print_export_list(t_env *env, t_data *data);
void						export_args_handle(t_cmd *cmd, char *key, char *value, t_data *data);
int							check_valid_name(char *name);
void						export_not_valid(char *tmp, int *i, char *value, char *key, t_data *data);
		//exit_utils
void						exit_norm(t_cmd *cmd, int *exit_status, pid_t pid, t_data *data);
long long					num(t_cmd *cmd, size_t min_limit, int last);
void						num_norm(t_cmd *cmd, int *i, int *sign);
void						exit_status(char *failed, int code, t_data *data);
		//cd_utils
int							change_dir(char *path, pid_t pid, t_data *data);
void						change_dir_norm(char *old_pwd, t_data *data);
char						*cd_error(t_cmd *cmd, pid_t pid, t_data *data);
		//exec_utils
int							count_commands(t_cmd *cmd);
void						exec_one_command(t_cmd *cmd, t_data *data);
void						error_display(t_cmd *cmd);
void						error_display_norm(t_cmd *cmd);
int							check_builtins(t_data *data, t_cmd *cmd, pid_t pid);
int							before_child(t_cmd *cmd, t_data *data);
char						**convert_path_to_array(t_env *env, t_data *data);
void						convert_path_to_arr_norm(t_env *tmp, char **paths, int *i, t_data *data);
int							get_size(t_env *env);
		//pipe_utils
void						create_pipe(t_cmd *cmds, int cmd_count, t_data *data);
void						forking_accordingly(t_cmd *cmd, int cmd_count, int *fd, t_data *data);
void						child_process(t_cmd *cmd, int *fd, int i, int cmd_count);
void						execute_cmd(t_cmd *cmd, int cmd_count, int *fd, int i, t_data *data);
void						close_fds(int cmd_count, int *fd);
void						pipe_utils(t_cmd *cmd, int status, t_data *data);
		//signals
void						sigint_handler(int signo);
void						sigquit_handler(int signo);
					//executor
int							execute_commands(t_data *data);
		//test
char						*find_full_path(char *cmd, t_env *env);
t_env						*find_env(t_env *env, char *name);
void						free_char_array(char **arr);
#endif