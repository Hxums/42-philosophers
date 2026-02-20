NAME = philosophers

SRC = main.c ft_isdigit.c ft_atol.c routine.c

OBJS = ${SRC:.c=.o}

CC        = cc
RM        = rm -f
CFLAGS = -Wall -Wextra -Werror -pthread
INCS	=

all:    ${NAME}

.c.o:
	@${CC} ${CFLAGS} -c $< -o $@ $(INCS)

$(NAME): ${OBJS}
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Philosophers compilé avec succès"

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re