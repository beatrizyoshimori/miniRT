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

######################### MLX #################################
MLX_H			=		$(addprefix $(HEADER_PATH), mlx/)
MLX				=		$(addprefix $(MLX_H), libmlx42.a)

######################### LIBFT ###############################
LIBFT_H			=		$(addprefix $(LIBFT_PATH), $(HEADER_PATH))
LIBFT			=		$(addprefix $(LIBFT_PATH), libft.a)

######################### SOURCES #############################
PARSER			=		parser.c \
						set_data.c \
						validate_data.c \
						validate_elements.c \
						validate_numbers.c \
						validate_objects.c
UTILS			=		create.c \
						equal.c \
						error.c \
						operations.c \
						vector_operations.c
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
FLAGS			=		-lm -ldl -lglfw -pthread
LIBFT_FLAGS		=		-L$(LIBFT_PATH) -lft
FLAGS_EXTRA		=		-g3 -O3 -MP
FLAGS_MLX		=		-I$(MLX_H)

######################### RECIPES #############################
all:					$(LIBFT) $(NAME)

$(LIBFT):
						@make -C $(LIBFT_PATH) --no-print-directory

$(OBJECTS_PATH)%.o: %.c
						@mkdir -p $(dir $@)
						@$(CC) $(FLAGS_EXTRA) $(C_FLAGS) -c $< -o $@ $(FLAGS_MLX)

$(NAME):				$(OBJECTS)
						@$(CC) $(C_FLAGS) $(OBJECTS) $(MLX) $(FLAGS_MLX) $(FLAGS) $(LIBFT_FLAGS) -o $@

clean:
						@$(RM) $(OBJECTS_PATH)
						@make -C $(LIBFT_PATH) clean --no-print-directory

fclean:					clean
						@$(RM) $(NAME)
						@make -C $(LIBFT_PATH) fclean --no-print-directory

re:						fclean all

.PHONY:					all clean fclean re