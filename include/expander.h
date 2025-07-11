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

void						handle_word_token(t_elem *curr, int exit_code);
void						expand_tokens(t_elem *token, int exit_code);
void						handle_quoted_token(t_elem *curr, int exit_code);
char						*get_env_value(char *name);
char						*extract_var_name(char *str, int start, int *end);
char						*expand_exit_status(int exit_code);
char						*remove_quotes(char *content, enum e_type quote_type);
char						*expand_token_content(char *content, int exit_code, int should_expand);
char						*realloc_result(char *result, int *max_size, int needed);
int							is_valid_var_char(char c);
int							copy_var_value(char **res, int *len, int *max, char *val);
int							process_regular_char(char *content, int *i, t_expand_data *data);
int							process_expansion_loop(char *content, t_expand_data *data);
int							process_dollar_expansion(char *content, int *i, t_expand_data *data);
int							handle_special_var(char *name, int exit_code, char **value);

#endif