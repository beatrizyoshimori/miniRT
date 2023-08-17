######################### NAMES ###############################
NAME			=		miniRT

######################### PATHS ###############################
HEADER_PATH		=		includes/
LIBFT_PATH		=		libft/
OBJECTS_PATH	=		objects/
SOURCES_PATH	=		sources/
VPATH			=		$(SOURCES_PATH) \
						$(addprefix $(SOURCES_PATH),	parser \
														utils)

######################### LIBFT ###############################
LIBFT_H			=		$(addprefix $(LIBFT_PATH), $(HEADER_PATH))
LIBFT			=		$(addprefix $(LIBFT_PATH), libft.a)

######################### SOURCES #############################
PARSER			=		parser.c
UTILS			=		error.c
SOURCES			=		minirt.c \
						$(PARSER) \
						$(UTILS)

######################### OBJECTS #############################
OBJECTS			=		$(patsubst %.c, $(OBJECTS_PATH)%.o, $(SOURCES))

######################### COMMANDS ############################
CC				=		cc
RM				=		rm -rf

######################### FLAGS ###############################
C_FLAGS			=		-Wall -Werror -Wextra -I$(HEADER_PATH) -I$(LIBFT_H)
LIBFT_FLAGS		=		-L$(LIBFT_PATH) -lft
FLAGS_EXTRA		=		-g3 -O3 -MP

######################### RECIPES #############################
all:					$(LIBFT) $(NAME)

$(LIBFT):
						@make -C $(LIBFT_PATH)

$(OBJECTS_PATH)%.o: %.c
						@mkdir -p $(dir $@)
						@$(CC) $(FLAGS_EXTRA) $(C_FLAGS) -c $< -o $@

$(NAME):				$(OBJECTS)
						@$(CC) $(C_FLAGS) $(OBJECTS) $(LIBFT_FLAGS) -o $@

clean:
						@$(RM) $(OBJECTS_PATH)
						@make -C $(LIBFT_PATH) clean

fclean:					clean
						@$(RM) $(NAME)
						@make -C $(LIBFT_PATH) fclean

re:						fclean all

.PHONY:					all clean fclean re