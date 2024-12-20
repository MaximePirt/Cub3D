#ifndef CUBE_H
#define CUBE_H

# include "../libft/include/libft.h"
# include "../minilibx/mlx.h"

# include "struct.h"
# include "window.h"

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

// Memory allocation

t_map	*ft_init_map(int size_x, int size_y);
t_block	*ft_init_block(void);
t_win	*ft_init_window(void);

// Memory free

int	ft_free_program(t_key_params *params);

// Player actions

int	player_move_forward(t_map *map);
int	player_move_backward(t_map *map);
int	player_look_left(t_map *map);
int	player_look_right(t_map *map);

#endif
