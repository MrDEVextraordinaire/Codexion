CC = cc
# CFLAGS = -Wall -Wextra -Werror -pthread -g
CFLAGS = -pthread -g
HEADER = includes/codexion.h
NAME = codexion

SRCS = main.c\
	utils/current_time.c\
	utils/parsed_validated.c\
	utils/valid_number.c\
	utils/atoull.c\
	utils/ft_strlen.c\
	utils/initializer.c\
	utils/cleanup.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

rec: fclean all
	make clean

.PHONY: all clean fclean re
