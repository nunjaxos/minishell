/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:44:35 by amouhand          #+#    #+#             */
/*   Updated: 2024/09/05 10:39:31 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "minishell.h"

typedef struct s_token			t_token;
typedef struct s_cmd			t_cmd;
typedef struct s_env			t_env;
typedef struct s_redirection	t_redirection;
typedef struct s_parser			t_parser;
typedef struct s_expand			t_expand;
typedef struct s_alloc			t_alloc;
typedef enum s_type				t_type;
typedef enum perms				t_perms;

char							**mini_parsing(char *commands,
									int **expand_check);
int								count_parse(char *commands);
void							allocate_cmd(t_cmd **cmd, t_token *head);
void							add_redirection(t_cmd *cmd,
									t_token *redir_token, char *arg);
int								count_args(t_token *start);
void							process_token(t_token **current,
									t_token **before, t_cmd **cmd, int i);
void							fill_args(t_token *start, t_token *end,
									t_cmd *cmd);
int								count_pipes(t_token *head);
void							initialize_cmd(t_cmd **cmd, t_token *current,
									int i);
t_cmd							**parse_cmd(t_token *head);
int								checking_parsing(t_token *head);
void							parsing_error(char *message, int status);
int								setting_parser(char *command, char ***result,
									int **expand_check);
int								set_path(t_cmd **cmd, t_env *env);
char							*get_path(char *command, char **path);
int								isspecial(char *command, int i);
int								unclosed_quotes(char *command);
t_env							*set_env(char **env);
int								copy_env(char *env, t_env *new);
void							free_env(t_env *head);
int								find_expand(char *command, int i);
int								count_char_array(char **commands);
void							fd_init(t_cmd **cmd);
char							*ft_strjoin_free(char *s1, char *s2, int flag);
int								open_heredoc(t_redirection *redir);
unsigned long					hash_djb2(const char *str);
int								heredoc_configuring(t_cmd **cmd);
int								heredoc_fd(t_cmd *cmd, t_redirection *redir);
int								check_for_quotes(char *command);
char							*expand_heredoc(char *line, int flag);
int								to_space(char *line, int i);
int								heredoc_arg(char *command, int i);
char							*quotes_in_heredoc(char *arg);
int								skip_segment(char *command, int i, int *j);
int								is_initial_special(char *command, int i);
int								handle_special_cases(char *command, int i,
									int tmp, int *check);
int								calculate_length(char *arg);
void							fill_result(char *arg, char *result);
int								calculate_new_length(char *line, int flag);
void							fill_heredoc(char *line, int flag,
									char *result);
char							*quotes_in_heredoc(char *arg);
void							fill_result(char *arg, char *result);
void							process_heredoc_lines(int fd,
									t_redirection *redir);
char							*generate_temp_filename(char *arg);
int								should_expand(char *command, int start);
int								copy_quote(char *command, int start,
									char *result, int *l);
int								if_builtin(char *arg);
void							edit_env(t_env *head, char *key,
									char *new_value);
void							test_binaries(t_cmd *cmd);
int								test_path(char **paths, t_cmd *cmd);
void							path_check(t_cmd *cmd, char **paths);
int								handle_parent_process(int fd, char *name,
									int pid);
int								finalize_heredoc(t_redirection *redir,
									char *name);
void							heredoc_signals(void);
int								heredoc_fd(t_cmd *cmd, t_redirection *redir);
int								close_and_open_input(t_cmd *cmd,
									t_redirection *redir);
int								close_and_open_output(t_cmd *cmd,
									t_redirection *redir);
int								close_and_open_append(t_cmd *cmd,
									t_redirection *redir);

#endif