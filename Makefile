CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

# 클러스터
# READLINE_LIB = -lreadline -L/goinfre/$(USER)/.brew/opt/readline/lib
# READLINE_INC = -I/goinfre/$(USER)/.brew/opt/readline/include

# MAC 인텔
 READLINE_LIB = -lreadline -L/usr/local/opt/readline/lib
 READLINE_INC = -I/usr/local/opt/readline/include

LIBFT = libft/libft.a

NAME = minishell

SRCS = src/minishell.c src/main_loop.c src/analize_line.c \
		src/utils/error_message.c src/utils/utils.c \
		src/signal/signal.c \
		src/tokenizer/process_token.c src/tokenizer/memory.c \
		src/tokenizer/tokenize.c src/tokenizer/tokenizer.c \

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