######################### NAMES ###############################
NAME			=		miniRT
NAME_B			=		miniRT_bonus

######################### PATHS ###############################
HEADER_PATH		=		includes/
HEADER_B_PATH	=		includes_bonus/
LIBFT_PATH		=		libft/
OBJECTS_PATH	=		objects/
OBJECTS_B_PATH	=		objects_bonus/
SOURCES_PATH	=		sources/
SOURCES_B_PATH	=		sources_bonus/
VPATH			=		$(SOURCES_PATH) \
						$(SOURCES_B_PATH) \
						$(addprefix $(SOURCES_PATH),	matrices \
														parser \
														ray_casting \
														render \
														tuples \
														utils) \
						$(addprefix $(SOURCES_B_PATH),	parser_bonus)

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
						rotation_matrices_objects.c \
						transformations_matrices_objects.c \
						transformations_matrices.c
PARSER			=		parser.c \
						set_data.c \
						validate_data.c \
						validate_elements.c \
						validate_numbers.c \
						validate_objects.c
RAY_CASTING		=		discriminant.c \
						intersection_ray_object.c \
						intersections.c \
						list_utils.c \
						normal_reflecting.c \
						ray_utils.c
RENDER			=		lightning.c \
						render.c
TUPLES			=		color_operations.c \
						comparison.c \
						create.c \
						operations.c \
						vector_operations.c
UTILS			=		error.c \
						free.c
SOURCES			=		minirt.c \
						$(MATRICES) \
						$(PARSER) \
						$(RAY_CASTING) \
						$(RENDER) \
						$(TUPLES) \
						$(UTILS)

PARSER_B		=		parser_bonus.c \
						set_data.c \
						validate_data.c \
						validate_elements.c \
						validate_numbers.c \
						validate_objects.c
SOURCES_B		=		minirt.c \
						$(MATRICES) \
						$(PARSER_B) \
						$(RAY_CASTING) \
						$(RENDER) \
						$(TUPLES) \
						$(UTILS)

######################### OBJECTS #############################
OBJECTS			=		$(patsubst %.c, $(OBJECTS_PATH)%.o, $(SOURCES))
OBJECTS_B		=		$(patsubst %.c, $(OBJECTS_B_PATH)%.o, $(SOURCES_B))

######################### COMMANDS ############################
CC				=		cc
RM				=		rm -rf

######################### DIMENSIONS ##########################
ifeq ($(HEIGHT),)
HEIGHT=1000
endif
ifeq ($(WIDTH),)
WIDTH=1000
endif

######################### FLAGS ###############################
C_FLAGS			=		-Wall -Werror -Wextra -O3 -D HEIGHT=$(HEIGHT) -D WIDTH=$(WIDTH) -I$(HEADER_PATH) -I$(HEADER_B_PATH) -I$(LIBFT_H)
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

bonus:					$(LIBFT) $(NAME_B)

$(OBJECTS_B_PATH)%.o:	%.c $(HEADER_B_PATH)minirt_bonus.h $(HEADER_B_PATH)error_bonus.h
						@mkdir -p $(dir $@)
						@$(CC) $(FLAGS_EXTRA) $(C_FLAGS) -c $< -o $@ $(FLAGS_MLX)

$(NAME_B):				$(OBJECTS_B)
						@$(CC) $(C_FLAGS) $(OBJECTS_B) $(MLX) $(FLAGS_MLX) $(FLAGS) $(LIBFT_FLAGS) -o $@

clean:
						@$(RM) $(OBJECTS_PATH) $(OBJECTS_B_PATH)
						@make -C $(LIBFT_PATH) clean --no-print-directory

fclean:					clean
						@$(RM) $(NAME) $(NAME_B)
						@make -C $(LIBFT_PATH) fclean --no-print-directory

re:						fclean all

re-size:				re

.PHONY:					all bonus clean fclean re