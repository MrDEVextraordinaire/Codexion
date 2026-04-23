CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
NAME = codexion

SRCS = main.c\
	utils/utils.c
	
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: codexion
	./codexion

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

rec: fclean all
	make clean

.PHONY: all, clean, fclean, re
