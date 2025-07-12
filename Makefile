PRINTA  = libftprintf.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -f

SRCS	= ./src/server.c
SRCC	= ./src/client.c

SRCS_BONUS	= ./src/server_bonus.c
SRCC_BONUS	= ./src/client_bonus.c

sc:
	$(CC) $(CFLAGS) $(SRCS) -o server
	$(CC) $(CFLAGS) $(SRCC) -o client
	$(CC) $(CFLAGS) $(SRCS_BONUS) $(PRINTA) -o server_bonus
	$(CC) $(CFLAGS) $(SRCC_BONUS) $(PRINTA) -o client_bonus

all: sc 

reall: all

