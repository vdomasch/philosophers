NAME				=	philo

SRCS_DIR			=	srcs

OBJS_DIR			=	.objs

HEADER_DIR			=	./

FILES				=	main.c			\
						checks.c		\
						init.c			\
						routine.c		\
						safe_get.c		\
						safe_set.c		\
						utils.c			\
						libft.c			\
						
OBJS				=	$(FILES:%.c=$(OBJS_DIR)/%.o)

HEADERS				=	$(HEADER_DIR)/$(NAME).h

CC					=	cc

FLAGS				=	-Wall -Werror -Wextra

DFLAGS				=	-fsanitize=address -g3


ifeq ($(DEBUG),true)
	FLAGS = -Wall -Werror -Wextra $(DFLAGS)
endif

all:				$(OBJS_DIR) $(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c $(HEADERS)
						$(CC) $(FLAGS) -c $< -o $@

$(NAME):			$(OBJS_DIR) $(OBJS) $(HEADERS) Makefile
						$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR):
						mkdir -p $(OBJS_DIR)

clean:
						rm -rf $(OBJS_DIR)

fclean:
						$(MAKE) clean
						rm -rf $(NAME)

re:
						$(MAKE) fclean all

debug				:
							@$(MAKE) fclean all DEBUG=true

.PHONY: all clean fclean re libft debug