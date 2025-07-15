NAME_MANDATORY	= server client
NAME_BONUS		= server_bonus client_bonus

SRCS_MANDATORY	= src/server.c src/client.c
SRCS_BONUS		= src/server_bonus.c src/client_bonus.c

OBJS_MANDATORY	= $(SRCS_MANDATORY:.c=.o)
OBJS_BONUS		= $(SRCS_BONUS:.c=.o)

CC				= gcc


INCLUDES		= -I ./includes -I ./ft_printf
CFLAGS			= -Wall -Wextra -Werror $(INCLUDES)

FT_PRINTF_DIR	= ./ft_printf
FT_PRINTF		= $(FT_PRINTF_DIR)/libftprintf.a


all: $(NAME_MANDATORY)

bonus: $(NAME_BONUS)

server: src/server.o $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $@ $^

client: src/client.o $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $@ $^

server_bonus: src/server_bonus.o $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $@ $^

client_bonus: src/client_bonus.o $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $@ $^


$(FT_PRINTF):
	@$(MAKE) -C $(FT_PRINTF_DIR)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	@rm -f $(OBJS_MANDATORY) $(OBJS_BONUS)
	@$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	@rm -f $(NAME_MANDATORY) $(NAME_BONUS)
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all
re_bonus: fclean bonus


.PHONY: all bonus clean fclean re re_bonus