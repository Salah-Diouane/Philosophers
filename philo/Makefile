NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = init.c \
			utils.c \
			threads.c \
			monitor.c \
			routine_actions.c \
			main.c \
			parsing.c 

OBJ = $(SRC:%.c=%.o)

B_OBJ = $(B_SRCS:%.c=%.o)

all: $(NAME)	

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf  $(OBJ)

fclean: 
	@rm -rf $(OBJ) $(NAME)

re: fclean all
