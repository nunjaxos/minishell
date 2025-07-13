#ifndef EXECUTOR
# define EXECUTOR

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
# include "parser.h"

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

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_cmd
{
	int				in_file;
	int				out_file;
	char			**full_cmd;
	int				access;
	pid_t			pid;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_alloc
{
	void					*allocated;
	struct s_alloc			*next;
}							t_alloc;

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
	t_alloc			*alloc;
	struct s_env	*n_env;
}				t_data;

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

typedef struct s_redirection
{
	t_token					*redir;
	char					*arg;
	int						fd;
	struct s_redirection	*next;
}							t_redirection;

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

typedef struct s_exec
{
	t_cmd			*cmds;
	t_env			*env;
	int				n_pipes;
	int				**pipes;
}							t_exec;
                //executor
int								count_commands(t_cmd *cmd);
int								execute_commands(t_data *data);
void							child_process(t_cmd **cmd, int *fd, int i,
									int cmd_count);
void							exit_status(char *failed, int status);
int								check_builtins(t_parser *parser, t_cmd *cmd,
									pid_t pid);
void							close_fds(int cmd_count, int *fd);
void							forking_accordingly(t_cmd *cmd, int cmd_count, int *fd,
									t_data *data);
void							exec_one_command(t_cmd *cmd, t_parser *parser);
int								count_all_commands(t_cmd **cmds);
void							create_pipe(t_cmd *cmds, int cmd_count, t_data *data);
char							**convert_path_to_array(t_env *env,t_data *data);
char							*get_valid_path(t_cmd *cmd, pid_t pid, t_data *data);
int								get_size(t_env *env);
void							update_pwd(t_env *env, t_data *data);
int								before_child(t_cmd *cmd, t_data *data);
void							convert_path_to_arr_norm(t_env *tmp,
									char **paths, int *i, t_data *data);
void							execute_cmd(t_cmd **cmd, int cmd_count, int *fd,
									int i);
void							error_display_norm(t_cmd *cmd);
int								*get_lastpid(void);
void							pipe_utils(t_cmd *cmd, int status, t_data *data);
void							one_cmd_norm(t_cmd *cmd, t_parser *parser,
									pid_t pid);
int								key_len(char *str);
int								str_index(const char *str, int ch);
                //builtins
void							ft_echo(t_cmd *cmd, pid_t pid, t_data *data);
void							ft_env(t_env *env, pid_t pid);
void							ft_pwd(pid_t pid, t_data *data);
void							ft_unset(t_cmd *cmd, pid_t pid, t_data *data);
int								ft_exit(t_cmd *cmd, pid_t pid, t_data *data);
int								ft_cd(t_cmd *cmd, pid_t pid, t_data *data);
int								ft_export(t_cmd *cmd, t_data *data);

void							add_env(t_env **head, char *key, char *value);
void							free_env_list(t_env *env);
void							init_env_list(char **envp, t_env **env_list);
void							print_export_list(t_env *env);
void							sort_env_list(t_env *env);
int								env_name_exists(t_env *env, char *name);
int								check_valid_name(char *name);
t_env							*copy_env_list(t_env *env);
void							error_display(t_cmd *cmd);
int								check_for_child(pid_t pid, int exit_stat, t_data *data);
char							*cd_error(t_cmd *cmd, pid_t pid, t_data *data);
int								export_error_display(t_cmd *cmd, char *key,
									char *value, int *i, t_data *data);
int								export_null(int *i, t_cmd *cmd, t_data *data);
void							export_args_handle(t_cmd *cmd, char *key,
									char *value, t_data *data);
void							exit_norm(t_cmd *cmd, int *exit_status,
									pid_t pid , t_data *data);
int								change_dir(char *path, pid_t pid, t_data *data);
void							change_dir_norm(char *old_pwd, t_data *data);
void							redic_error(t_redirection *redirection);
void							export_not_valid(char *tmp, int *i,
									char *value, char *key);
long long						num(t_cmd *cmd, size_t min_limit, int last);
void							num_norm(t_cmd *cmd, int *i, int *sign);
int								check_for_doubles(char *args);
int								ft_strcmp(char *s1, char *s2);
char							*get_value(char *key, t_env *env);
void							delete_env(t_env *env, char *key, t_data *data);
                //signals
void							sigint_handler(int signo, t_data *data);
void							sigquit_handler(int signo, t_data *s_data);
				//utils
int								handle_regular_characters(char *command, int i,
									int *l, int *tmp);
void							check_init(size_t *i, int *j,
									int *k, int *digit);
int								handle_quotes(char *command, int i, int *l,
									int *tmp);
int								handle_special_characters(char *command, int i,
									int *l);
int								skip_whitespace(char *command, int i);
int								skip_quotes(char *command, int i);
int								skip_special_char(char *command, int i);
int								skip_everything_else(char *command, int i);
char							*copy_segment(char *command, int start, int end,
									int *expand_check);
void							free_tokens(t_token **head, t_data *data);
void							free_char_array(char **array, t_data *data);
void							free_cmd(t_cmd *cmd);
void							free_redirections(t_redirection *redirections);
void							free_data(t_data *data);
char							*set_cwd(void);
int								ft_isspace(char charac);
char							**further_split(char *s, char *charset);
t_env							*check_env(void);
void							env_update(t_env *env);
int								ft_atoi_shlvl(char *shlvl);
void							check_shlvl(t_env *env);
void							update_last_cmd(t_parser *parser);
void							*ft_malloc(size_t size, t_alloc **alloc);
void							add_alloc(void *allocated, t_alloc **alloc);
void							garbage_removal(t_alloc **alloc);
void							ft_free(void *ptr, t_alloc **alloc);
void							heredoc_signals(void);
void							edit_env(t_env *head, char *key, char *new_value);
int								undeflow_check(size_t min_limit, size_t test,
									int digit, int last);
int								overflow_check(size_t test, int digit);
int								ft_strslen(char **strs);
char							*ft_strndup(const char *s, size_t n);
#endif