#---COMMON_VAR-----------------------------------
NAME		=	philo
CC			=	cc
FLAGS		=	-Wall -Werror -Wextra -pthread -fsanitize=address -g3
#---PHILO_VAR----------------------------------
SRC			=	srcs/main.c \
				srcs/parsing/ft_atoll.c \
				srcs/parsing/parsing.c \
				srcs/parsing/threads.c \
				srcs/routine/routine.c
OBJS_DIR	=	.OBJS/
OBJS		=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))
HEADER_DIR	=	header/
HEADER		=	header/philo.h \
#---RULES----------------------------------------

all:			$(NAME)

$(NAME):		$(OBJS) $(HEADER)
				@echo "\033[0;33m\nCOMPILING PHILO...\n"
				@$(CC) $(FLAGS) -I $(HEADER_DIR) $(OBJS) -o $@
				@echo "\033[1;32m./philo created\n"

$(OBJS_DIR)%.o:	%.c $(HEADER) | dir
				$(CC) $(FLAGS) -I $(HEADER_DIR) -c $< -o $@

dir:			$(OBJS_DIR)

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)
				@mkdir -p $(OBJS_DIR)srcs
				@mkdir -p $(OBJS_DIR)srcs/parsing
				@mkdir -p $(OBJS_DIR)srcs/routine

clean:
				@echo "\033[0;31mDeleting philo object...\n"
				@$(RM) -rf $(OBJS_DIR)
				@echo "\033[1;32mDone\n"

fclean:			clean
				@echo "\033[0;31mDeleting philo executable..."
				@rm -rf $(NAME)
				@echo "\033[1;32mDone\n"

re:				fclean all

.PHONY:			all clean fclean re