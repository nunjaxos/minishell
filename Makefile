# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 22:18:52 by amouhand          #+#    #+#              #
#    Updated: 2024/09/05 22:21:00 by amouhand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

CC = cc

CFLAGS = -g3

SPECIALFLAGS = -lreadline -lncurses

SRC =   src/main.c src/utils/cmd_utils.c src/parser/parser_utils.c src/parser/parser.c\
                src/lexer/lexer.c src/lexer/lexer_utils.c\
                src/parser/parser_cmd.c src/parser/parser_cmd_utils.c src/parser/parsing_error.c\
                src/utils/parsing_utils.c src/parser/testing_commands.c src/parser/parse_env.c\
                src/executor/executor.c src/builtins/cd.c src/utils/free_stuff.c\
                src/signals/singal_handling.c src/utils/set_env.c src/expander/expander.c\
                src/parser/heredoc.c src/utils/heredoc_utils.c src/parser/fd_init.c\
                src/utils/heredoc_utils2.c src/utils/parsing_utils2.c src/parser/fd_management.c\
                src/expander/expander_plus.c src/expander/expander_plusplus.c\
                src/utils/cringe_norm.c src/executor/pipe_utils.c src/executor/executor_utils.c\
                src/executor/pipe_handle.c src/builtins/env.c src/builtins/exit.c\
                src/builtins/echo.c src/builtins/pwd.c src/builtins/export.c src/builtins/unset.c\
                src/builtins/built_utils.c src/executor/exec_utils.c src/executor/more_utils.c\
                src/utils/main_utils.c src/utils/further_split.c src/allocation_wrapper/allocation.c\
                src/expander/expander_extra.c src/expander/expander_extra_extra.c src/allocation_wrapper/freeing.c\
                src/utils/env.c src/utils/expander_utils.c src/expander/expander_split_handling.c\
                src/builtins/further_more_utils.c src/utils/cringe_norm2.c src/utils/builtins_helpers.c\

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

