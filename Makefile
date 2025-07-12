LIBA	= libft.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -f

SRCS	= ./src/server.c
SRCC	= ./src/client.c

sc:
	$(CC) $(CFLAGS) $(SRCS) $(LIBA) -o server
	$(CC) $(CFLAGS) $(SRCC) $(LIBA) -o client

all: sc

reall: all
