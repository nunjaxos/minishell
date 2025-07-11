#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"

typedef struct s_token			t_token;
typedef struct s_cmd			t_cmd;
typedef struct s_env			t_env;
typedef struct s_redirection	t_redirection;
typedef struct s_parser			t_parser;
typedef struct s_expand			t_expand;
typedef struct s_alloc			t_alloc;
typedef enum s_type				t_type;
typedef enum perms				t_perms;

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
char							**convert_path_to_array(t_env *env);
char							*get_valid_path(t_cmd *cmd, pid_t pid);
int								get_size(t_env *env);
void							update_pwd(t_env *env);
int								before_child(t_cmd *cmd);
void							convert_path_to_arr_norm(t_env *tmp,
									char **paths, int *i);
void							execute_cmd(t_cmd **cmd, int cmd_count, int *fd,
									int i);
void							error_display_norm(t_cmd *cmd);
int								*get_lastpid(void);
void							pipe_utils(t_cmd *cmd, int status, t_data *data);
void							one_cmd_norm(t_cmd *cmd, t_parser *parser,
									pid_t pid);
int								key_len(char *str);
int								str_index(const char *str, int ch);

#endif