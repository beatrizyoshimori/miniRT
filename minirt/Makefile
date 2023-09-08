######################### NAMES ###############################
NAME			=		miniRT

######################### PATHS ###############################
HEADER_PATH		=		includes/
LIBFT_PATH		=		libft/
OBJECTS_PATH	=		objects/
SOURCES_PATH	=		sources/
VPATH			=		$(SOURCES_PATH) \
						$(addprefix $(SOURCES_PATH),	matrices \
														parser \
														ray_casting \
														tuples \
														utils)

######################### MLX #################################
MLX_H			=		$(addprefix $(HEADER_PATH), mlx/)
MLX				=		$(addprefix $(MLX_H), libmlx42.a)

######################### LIBFT ###############################
LIBFT_H			=		$(addprefix $(LIBFT_PATH), $(HEADER_PATH))
LIBFT			=		$(addprefix $(LIBFT_PATH), libft.a)

######################### SOURCES #############################
MATRICES		=		comparison_matrices.c \
						create_matrix.c \
						determinant.c \
						operations_matrices.c \
						transformations.c
PARSER			=		parser.c \
						set_data.c \
						validate_data.c \
						validate_elements.c \
						validate_numbers.c \
						validate_objects.c
RAY_CASTING		=		intersection_ray_sphere.c \
						intersections.c \
						list_utils.c \
						ray_utils.c \
						transformation.c
TUPLES			=		create.c \
						comparison.c \
						operations.c \
						vector_operations.c
UTILS			=		error.c \
						free.c
SOURCES			=		minirt.c \
						render.c \
						$(MATRICES) \
						$(PARSER) \
						$(RAY_CASTING) \
						$(TUPLES) \
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

$(OBJECTS_PATH)%.o:		%.c $(HEADER_PATH)minirt.h $(HEADER_PATH)error.h
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