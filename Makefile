NAME = philo

SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, checker.c ft_atol.c ft_isdigit.c generator.c main.c \
	monitor.c routine.c utils.c utils2.c)

OBJS = ${SRC:.c=.o}

CC        = cc
RM        = rm -f
CFLAGS = -Wall -Wextra -Werror -pthread -g3
INCS	=

all:    ${NAME}

.c.o:
	@${CC} ${CFLAGS} -c $< -o $@ $(INCS)

$(NAME): ${OBJS}
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Build complete! Executable: $(NAME)"


clean:
	@${RM} ${OBJS}
	@echo "🧹 Object files removed."


fclean: clean
	@${RM} ${NAME}
	@echo "🗑️  All cleaned (objects + executable)."


re: fclean all
	@echo "🔄 Full rebuild done."

.PHONY: all clean fclean re