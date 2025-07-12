LIB = ar rcs

NAME = libft.a

MY_SOURCES = ft_isalnum.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_isascii.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_bzero.c\
		ft_strncmp.c\
		ft_memcpy.c\
		ft_memchr.c\
		ft_memmove.c\
		ft_memcmp.c\
		ft_memset.c\
		ft_atoi.c\
		ft_strnstr.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_strlen.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_split.c\
		ft_str_is_only_space.c\
		ft_isprint.c
	
MY_OBJECTS = $(MY_SOURCES:.c=.o)

MY_SOURCES_BONUS = 	ft_lstnew_bonus.c\
					ft_lstsize_bonus.c\
					ft_lstlast_bonus.c\
					ft_lstadd_back_bonus.c\
					ft_lstdelone_bonus.c\
					ft_lstclear_bonus.c\
					ft_lstiter_bonus.c\
					ft_lstmap_bonus.c\
					ft_lstadd_front_bonus.c

MY_OBJECTS_BONUS = $(MY_SOURCES_BONUS:.c=.o)

CC = gcc

CFLAGS += -Wall -Wextra -Werror

BONUS_CACHE = .cache

$(NAME): $(MY_OBJECTS) libft.h
	$(LIB) $(NAME) $(MY_OBJECTS)

$(BONUS_CACHE): $(MY_OBJECTS_BONUS)
		$(LIB) $(NAME) $(MY_OBJECTS_BONUS)
		@touch $(BONUS_CACHE)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

bonus: $(BONUS_CACHE)

all: $(NAME)

clean:
	rm -f $(MY_OBJECTS) $(MY_OBJECTS_BONUS) $(BONUS_CACHE)

fclean: clean
	rm -f $(NAME)
	
re:     fclean all

.PHONY: all clean fclean re bonus
