/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:56:00 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/30 19:54:30 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include <stdbool.h>

typedef struct s_token			t_token;
typedef struct s_cmd			t_cmd;
typedef struct s_env			t_env;
typedef struct s_redirection	t_redirection;
typedef struct s_parser			t_parser;
typedef struct s_expand			t_expand;
typedef struct s_alloc			t_alloc;
typedef enum s_type				t_type;
typedef enum perms				t_perms;

int								expander(t_cmd **cmds);
char							*expand_env(char *arg, int flag);
char							*joining(char *to_free, char *before,
									char *expand, char *after);
char							*get_before(char *arg);
char							*get_expand(char *expand, int flag);
char							*get_value(char *key, t_env *env);
char							*get_after(char *arg);
char							*handle_key_conditions(char *key, int flag,
									char *expand);
char							*extract_key(char *expand);
void							process_characters(char *arg, int *i,
									int *check, int *tmp);
char							*remove_quotes(char *arg, int *flag);
int								count_chars_without_quotes(char *arg,
									int *flag);
void							copy_chars_without_quotes(char *result,
									char *arg, int *flag);
void							init_vars(int *i, int *j, int *tmp);
void							increment_vars(int *i, int *j, int *k, int *l);
void							set_check(char *arg, int *i, int *flag);
void							set_and_increment(int *i, int *flag);
char							**expand_space(t_cmd *cmd, int *j,
									char **expanded);
int								space_available(char *arg);
void							ambiguos_redirect(char *arg);
char							**further_split(char *s, char *charset);
char							**replace_null(char **arr, int index);
void							add_to_expand(void);
void							expand_list_process(char *before, int flag,
									int expand);
void							add_content_to_expand(char *content);
void							add_should_split_to_expand(bool should_split);
void							add_in_single_quotes_to_expand(
									bool in_single_quotes);
void							add_in_double_quotes_to_expand(
									bool in_double_quotes);
void							free_expand_list(void);
char							**joining_expand_list(t_cmd *cmd);
int								calculate_result_size(t_expand *expand);
void							fill_result_array(char **result,
									t_expand *expand);
void							assignment_split_check(char **argument,
									t_expand *expand);
int								expand_redirections(t_redirection *re);
void							expand_command(t_cmd *cmd);
char							*process_before(char *arg, int *flag);
char							*process_expand_and_after(char *arg,
									char *before, int flag);
void							update_split_flag(t_expand *expand,
									t_expand *prev, int flag);
int								find_split_flag(t_expand *expand,
									t_expand *prev);

#endif