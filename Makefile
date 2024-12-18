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

NAME					= cube3d

#############################################################################
#									SOURCES									#
#############################################################################

SRCS					= main.c

SRCS_PARSING            = floodfill.c floodfill_utils.c parsing.c parsing_utils.c

SRC_MEMORY				= memory_alloc.c memory_free.c window_alloc.c

SRC_GAME				= keymap.c player.c

SRC_RENDERING			= rendering.c

#############################################################################
#									FOLDERS									#
#############################################################################

SRCS_PARSING			:= $(addprefix parsing$(DIRSEP), $(SRCS_PARSING))

SRC_MEMORY				:= $(addprefix memory$(DIRSEP), $(SRC_MEMORY))

SRC_GAME				:= $(addprefix game$(DIRSEP), $(SRC_GAME))

SRC_RENDERING			:= $(addprefix rendering$(DIRSEP), $(SRC_RENDERING))

SRCS					+= $(SRCS_PARSING)

SRCS					:= $(addprefix src$(DIRSEP), $(SRCS))

#############################################################################

OBJ_PATH		= obj$(DIRSEP)

OBJ_NAME		= $(SRCS:%.c=%.o)

OBJS			= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

CC				= cc

HEAD			= include

LIBFT_DIR		= libft

MINILIBX_DIR	= minilibx

CFLAGS			= -O2 -I $(HEAD) -MMD -MP

CFLAGS += -Wall -Wextra -Werror -g

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

$(OBJ_PATH)%.o : %.c
	@mkdir -p $(@D) 2> $(DIRSEP)dev$(DIRSEP)null || true
	@echo "$(YELLOW)Compiling $< $(DEFCOLOR)"
	@$(CC) $(CFLAGS) -o $@ -c $<

clean: libft_clean minilibx_clean
	@$(RM) -r $(OBJ_PATH) 2> $(DIRSEP)dev$(DIRSEP)null || true
	@echo "$(PURPLE)Object files have been removed.$(DEFCOLOR)"

fclean: libft_fclean minilibx_clean
	@$(RM) -r $(OBJ_PATH) 2> $(DIRSEP)dev$(DIRSEP)null || true
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) has been removed.$(DEFCOLOR)"

re: fclean all

.PHONY: libft libft_clean libft_fclean all clean fclean re minilibx minilibx_clean