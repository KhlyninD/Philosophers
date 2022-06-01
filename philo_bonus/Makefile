
NAME            = philo_bonus
CC              = cc
CFALGS          = -O2 -Wall -Wextra -Werror -lpthread
RM              = rm -rf
SRC_DIR         = src/
HEADER          = ./inc/philo_bonus.h
SRC_FILES       = philo_bonus.c\
					check_init_bonus.c\
					utils_bonus.c\
					tread_bonus.c

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