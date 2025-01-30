#############################################################################
#									OS										#
#############################################################################

ifeq ($(OS), Windows_NT)
	DIRSEP	= \\
	CP		= copy
	RM		= del -f
else
	DIRSEP	= /
	CP		= cp
	RM		= rm -f
endif

NAME					= cube3D
NAME_BONUS				= cube2D_bonus # A little tribute to nitpicky graders :)

#############################################################################
#									SOURCES									#
#############################################################################

SRCS					= main.c

SRCS_PARSING            = parsing.c copy_tab_to_map.c lst_parsing$(DIRSEP)lst_pars_lib.c \
							floodfill.c floodfill_utils.c check_first_lines.c textures.c

SRC_MEMORY				= memory_alloc.c memory_free.c window_alloc.c textures_alloc.c image_alloc.c ray_alloc.c ray_free.c

SRC_GAME				= game.c keymap.c player.c player_movement.c

SRC_RENDERING			= rendering.c vectors.c minimap.c drawer$(DIRSEP)brushs.c \
							drawer$(DIRSEP)shapes$(DIRSEP)circle.c \
							drawer$(DIRSEP)shapes$(DIRSEP)square.c raycast$(DIRSEP)raycasting.c \
							drawer$(DIRSEP)shapes$(DIRSEP)rectangle.c drawer$(DIRSEP)image_tools.c \
							drawer$(DIRSEP)draw.c

#############################################################################
#									SOURCES_BONUS							#
#############################################################################

SRCS_BONUS				= main_bonus.c

SRCS_PARSING_BONUS		= parsing_bonus.c copy_tab_to_map_bonus.c lst_parsing$(DIRSEP)lst_pars_lib_bonus.c \
							floodfill_bonus.c floodfill_utils_bonus.c check_first_lines_bonus.c textures_bonus.c

SRC_MEMORY_BONUS		= memory_alloc_bonus.c memory_free_bonus.c window_alloc_bonus.c textures_alloc_bonus.c \
							image_alloc_bonus.c ray_alloc_bonus.c ray_free_bonus.c

SRC_GAME_BONUS			= game_bonus.c keymap_bonus.c player_bonus.c player_movement_bonus.c

SRC_RENDERING_BONUS		= rendering_bonus.c vectors_bonus.c minimap_bonus.c drawer$(DIRSEP)brushs_bonus.c \
							drawer$(DIRSEP)shapes$(DIRSEP)circle_bonus.c \
							drawer$(DIRSEP)shapes$(DIRSEP)square_bonus.c raycast$(DIRSEP)raycasting_bonus.c \
							drawer$(DIRSEP)shapes$(DIRSEP)rectangle_bonus.c drawer$(DIRSEP)image_tools_bonus.c \
							drawer$(DIRSEP)draw_bonus.c



#############################################################################
#									FOLDERS									#
#############################################################################

SRCS_PARSING			:= $(addprefix parsing$(DIRSEP), $(SRCS_PARSING))

SRC_MEMORY				:= $(addprefix memory$(DIRSEP), $(SRC_MEMORY))

SRC_GAME				:= $(addprefix game$(DIRSEP), $(SRC_GAME))

SRC_RENDERING			:= $(addprefix rendering$(DIRSEP), $(SRC_RENDERING))

SRCS					+= $(SRC_MEMORY) $(SRC_GAME) $(SRC_RENDERING) $(SRCS_PARSING)

SRCS					:= $(addprefix src$(DIRSEP), $(DIRSEP)$(SRCS))


#############################################################################
#								FOLDERS_BONUS								#
#############################################################################

SRCS_PARSING_BONUS		:= $(addprefix parsing$(DIRSEP), $(SRCS_PARSING_BONUS))

SRC_MEMORY_BONUS		:= $(addprefix memory$(DIRSEP), $(SRC_MEMORY_BONUS))

SRC_GAME_BONUS			:= $(addprefix game$(DIRSEP), $(SRC_GAME_BONUS))

SRC_RENDERING_BONUS		:= $(addprefix rendering$(DIRSEP), $(SRC_RENDERING_BONUS))

SRCS_BONUS				+= $(SRC_MEMORY_BONUS) $(SRC_GAME_BONUS) $(SRC_RENDERING_BONUS) $(SRCS_PARSING_BONUS)

SRCS_BONUS				:= $(addprefix src$(DIRSEP), $(SRCS_BONUS))

#############################################################################

OBJ_PATH		= obj$(DIRSEP)

OBJ_NAME		= $(SRCS:%.c=%.o)

OBJS			= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

OBJS_PATH_BONUS	= obj_bonus$(DIRSEP)

OBJ_NAME_BONUS	= $(SRCS_BONUS:%.c= %.o)

OBJ_BONUS		= $(addprefix $(OBJS_PATH_BONUS), $(OBJ_NAME_BONUS))

CC				= cc

HEAD			= include

LIBFT_DIR		= libft

MINILIBX_DIR	= minilibx

CFLAGS			= -O2 -I $(HEAD) -MMD -MP

CFLAGS += -g -Wall -Wextra -Werror

#VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes # --suppressions=vsupp

# COLORS
DEFCOLOR = \033[0;39m
GREEN    = \033[1;92m
YELLOW   = \033[0;93m
PURPLE   = \033[0;95m
RED		 = \033[0;91m

$(NAME): $(OBJS) libft minilibx
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(LIBFT_DIR) -lft -L $(MINILIBX_DIR) -lft -lmlx -lXext -lX11 -lm
	@echo "$(GREEN)$(NAME) has been created successfully.$(DEFCOLOR)"

libft:
	@make -C $(LIBFT_DIR)

libft_clean:
	@make -C $(LIBFT_DIR) clean

libft_fclean:
	@make -C $(LIBFT_DIR) fclean

minilibx:
	@make -C $(MINILIBX_DIR)

minilibx_clean:
	@make -C $(MINILIBX_DIR) clean

all: $(NAME)

$(OBJ_PATH)%.o : mandatory$(DIRSEP)%.c
	@mkdir -p $(@D) 2> $(DIRSEP)dev$(DIRSEP)null || true
	@echo "$(YELLOW)Compiling $< $(DEFCOLOR)"
	@$(CC) $(CFLAGS) -Imandatory/include -o $@ -c $<

$(NAME_BONUS): $(OBJ_BONUS) libft minilibx
	@$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) -L $(LIBFT_DIR) -lft -L $(MINILIBX_DIR) -lft -lmlx -lXext -lX11 -lm
	@echo "$(GREEN)$(NAME_BONUS) has been created successfully.$(DEFCOLOR)"

$(OBJS_PATH_BONUS)%.o : bonus$(DIRSEP)%.c
	@mkdir -p $(@D) 2> $(DIRSEP)dev$(DIRSEP)null || true
	@echo "$(YELLOW)Compiling $< with CFLAGS: $(CFLAGS) $(DEFCOLOR)$(DEFCOLOR)"
	@$(CC) $(CFLAGS) -I bonus/include -o $@ -c $<

clean: libft_clean minilibx_clean
	@$(RM) -r $(OBJ_PATH) $(OBJS_PATH_BONUS) 2> $(DIRSEP)dev$(DIRSEP)null || true
	@echo "$(PURPLE)Object files have been removed.$(DEFCOLOR)"

fclean: libft_fclean minilibx_clean
	@$(RM) -r $(OBJ_PATH) $(OBJS_PATH_BONUS) 2> $(DIRSEP)dev$(DIRSEP)null || true
	@$(RM) $(NAME) $(NAME_BONUS) 2> $(DIRSEP)dev$(DIRSEP)null || true
	@echo "$(RED)Program has been removed.$(DEFCOLOR)"

bonus: $(NAME_BONUS)

re: fclean all

gprof: CFLAGS += -pg
gprof: re
	./$(NAME) maps/lvl_2.cub
	gprof $(NAME) gmon.out > stats.txt
	@echo "Profiling complete. Results saved in stats.txt."

.PHONY: libft libft_clean libft_fclean all clean fclean bonus re minilibx minilibx_clean gprof