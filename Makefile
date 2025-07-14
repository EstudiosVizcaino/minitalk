NAME_SERVER = server
NAME_CLIENT = client
NAME_SERVER_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus

SRCS_SERVER = src/server.c
SRCS_CLIENT = src/client.c
SRCS_SERVER_BONUS = src/server_bonus.c
SRCS_CLIENT_BONUS = src/client_bonus.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Path to ft_printf directory
FT_PRINTF_DIR = ./ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
INCLUDES = -I$(FT_PRINTF_DIR)

# Default all targets (main + bonus)
all: $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

# Main program targets (server and client)
$(NAME_SERVER): $(OBJS_SERVER) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER) $(FT_PRINTF) $(INCLUDES)

$(NAME_CLIENT): $(OBJS_CLIENT) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT) $(FT_PRINTF) $(INCLUDES)

# Bonus program targets (server_bonus and client_bonus)
$(NAME_SERVER_BONUS): $(OBJS_SERVER_BONUS) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_SERVER_BONUS) $(OBJS_SERVER_BONUS) $(FT_PRINTF) $(INCLUDES)

$(NAME_CLIENT_BONUS): $(OBJS_CLIENT_BONUS) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT_BONUS) $(OBJS_CLIENT_BONUS) $(FT_PRINTF) $(INCLUDES)

# Rule to compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ft_printf build rule
$(FT_PRINTF):
	@$(MAKE) -C $(FT_PRINTF_DIR)

# Clean object files and temporary files
clean:
	@rm -f $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)
	@$(MAKE) -C $(FT_PRINTF_DIR) clean

# Clean up everything including binaries
fclean: clean
	@rm -f $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re

