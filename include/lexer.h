#ifndef LEXER_H
# define LEXER_H

# include "executor.h"

typedef struct s_token			t_token;
typedef struct s_cmd			t_cmd;
typedef struct s_env			t_env;
typedef struct s_redirection	t_redirection;
typedef struct s_parser			t_parser;
typedef struct s_expand			t_expand;
typedef struct s_alloc			t_alloc;
typedef enum s_type				t_type;
typedef enum perms				t_perms;

void                        init_data(t_data *data, char *input);
void                        append_token(t_elem **head, t_elem *new);
void                        handle_quote(const char *input, int *i, t_elem **head);
void                        merge_adjacent_word_tokens(t_elem **head);
t_lexer                     *init_lexer(char *input);
t_elem                      *create_token(char *content, enum e_type type, enum e_state state);
t_elem                      *init_tokens(t_lexer *lexer);
int                         process_single_char_token(t_lexer *lexer, t_elem **head,
                                char c, enum e_type type);
int                         process_special_chars(t_lexer *lexer, t_elem **head);
int                         process_exit_status(t_lexer *lexer, t_elem **head);
int                         process_escape_token(t_lexer *lexer, t_elem **head);
int                         handle_redirections(const char *input, int i, t_elem **head);
int                         handle_env(const char *input, int *i, t_elem **head);
int	                        create_content_token(const char *input, int start, int end,
							    t_elem **head, enum e_state state);
int                         handle_space(const char *input, int *i, t_elem **head);
int                         handle_word(const char *input, int i, t_elem **head);

#endif