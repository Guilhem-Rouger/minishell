SRCS =	src/main.c \
				src/setup.c \
				src/parsing/parsing_utils.c \
				src/parsing/quote.c \
				src/parsing/token.c \
				src/parsing/token_verif.c \
				src/list_utils/lst_token.c \
				src/list_utils/lst_env.c \
				src/list_utils/utils.c \
				src/list_utils/utils2.c \
				src/list_utils/split_quote.c \
				src/list_utils/split_sep.c \
				src/list_utils/split_sep2.c \
				src/built-in/echo.c \
				src/parsing/prompt.c \
				src/built-in/cd.c \
				src/built-in/export.c \
				src/built-in/env_utils.c \
				src/built-in/unset.c \
				src/built-in/exit.c \
				src/built-in/pwd.c \
				src/built-in/env.c \
				src/exec/check_exec.c \
				src/exec/exec.c \
				src/utils/clear.c \
				src/list_utils/utils3.c \
				src/list_utils/utils4.c \
				src/parsing/operator.c \
				src/parsing/parsing.c \
				src/list_utils/gnl.c
				src/debug.c
				
OBJS = $(SRCS:.c=.o)
NAME = minishell

LIBFT = libft/libft.a


all: LIBFT $(NAME)

LIBFT : 
	@$(MAKE) -C libft all
	@echo -e "\033[0;32m LIBFT OK\033[36m"

$(NAME) : $(OBJS)
	@gcc $(OBJS) $(LIBFT) -o $(NAME) -lreadline -lhistory
	@echo -e "\033[32m minicoque as compiled succesfully\033[0m"
	
%.o : %.c
	@gcc -Wall -Werror -Wextra -g $< -c -o $@
	
clean : 
	@$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean : clean
	@$(MAKE) -C libft fclean
	rm -f $(NAME)

re : fclean all