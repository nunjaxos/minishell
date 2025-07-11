NAME = minishell

LIBFT = libft/libft.a

CC = cc

CFLAGS = -g3

SPECIALFLAGS = -lreadline -lncurses

SRC =   src/main.c src/debugin.c src/utils/cmd_utils.c src/parser/handle_heredoc.c src/parser/handle_redirections.c\
                src/lexer/lexer_init.c src/lexer/lexer_special_handler.c\
                src/parser/parser_utils.c src/parser/parser.c \
                src/executor/executor.c src/builtins/cd.c src/utils/free_stuff.c\
                src/signals/singal_handling.c src/utils/set_env.c src/expand/expand_env.c\
                src/utils/heredoc_utils.c src/utils/heredoc_utils2.c\
                src/expand/expand_token.c src/expand/expand_utils.c\
                src/utils/cringe_norm.c src/executor/pipe_utils.c src/executor/executor_utils.c\
                src/executor/pipe_handle.c src/builtins/env.c src/builtins/exit.c\
                src/builtins/echo.c src/builtins/pwd.c src/builtins/export.c src/builtins/unset.c\
                src/builtins/built_utils.c src/executor/exec_utils.c src/executor/more_utils.c\
                src/utils/further_split.c src/allocation_wrapper/allocation.c\
                src/allocation_wrapper/freeing.c\
                src/utils/env.c src/builtins/further_more_utils.c src/utils/cringe_norm2.c src/utils/builtins_helpers.c\

OBJ = $(SRC:.c=.o)

all: $(NAME) 

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(SPECIALFLAGS) -g -o $(NAME)

$(LIBFT):
	@make -s -C libft

%.o : %.c
	@$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	@make clean -s -C libft
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -s -C libft

re: fclean all

.PHONY: all clean fclean re

