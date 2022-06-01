
NAME            = philo
CC              = cc
CFALGS          = -O2 -Wall -Wextra -Werror -lpthread
RM              = rm -rf
SRC_DIR         = src/
HEADER          = ./inc/philo.h
SRC_FILES       = philo.c\
					check_init.c\
					utils.c\
					tread.c

OBJS            = $(patsubst %.c, %.o, $(addprefix $(SRC_DIR), $(SRC_FILES)))

all:            $(NAME)

$(NAME)			: $(OBJS) $(HEADER) 
			$(CC) $(CFLAGS) $(OBJS) -o $@

$(SRC_DIR)%.o	: $(SRC_DIR)%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re:		fclean all
.PHONY: all clean fclean re