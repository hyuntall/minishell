CC = cc -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -Iinclude

# 클러스터
# READLINE_LIB = -lreadline -L/goinfre/$(USER)/.brew/opt/readline/lib
# READLINE_INC = -I/goinfre/$(USER)/.brew/opt/readline/include

# MAC 인텔
 READLINE_LIB = -lreadline -L/usr/local/opt/readline/lib
 READLINE_INC = -I/usr/local/opt/readline/include

LIBFT = libft/libft.a

NAME = minishell

SRCS = src/utils/testcode.c \
		src/minishell.c src/main_loop.c src/analize_line.c \
		src/utils/error_message.c src/utils/setting.c \
		src/signal/signal.c src/envp/envp_list.c src/envp/print_envp.c \
		src/tokenizer/process_token.c src/tokenizer/memory.c \
		src/tokenizer/tokenize.c src/tokenizer/tokenizer.c \
		src/parser/parser.c src/parser/insert_tree.c src/parser/token_tool.c \
		src/parser/parenthesis.c \
		src/lexer/lexer.c \
		src/heredoc/here_doc.c \
		src/exec_tree/order_tree.c \
		src/builtins/builtins.c src/builtins/echo.c src/builtins/pwd.c src/builtins/cd.c \
		src/builtins/env.c src/builtins/func.c

OBJS = $(SRCS:.c=.o)

all:  $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE_LIB) $(READLINE_INC)

$(LIBFT):
	@make -C ./libft

%.o: %.c
	@$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	@make clean -C libft/
	@rm -rf $(OBJS)

fclean: clean
	@make fclean -C libft/
	@rm -rf $(NAME) $(OBJS)

re: fclean 
	@$(MAKE)