#ifndef WINDOW_H
#define WINDOW_H

# define MOUSE_SENSITIVITY 2.5

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000
# define MINIMAP_RENDER_DISTANCE 8
# define RAYS_COUNT 1000
# define FOV 60
# define ANGLE (FOV/RAYS_COUNT)

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_T 116
# define KEY_ARROW_LEFT 65361
# define KEY_ARROW_RIGHT 65363

#define NORTH 270
#define EAST 0
#define SOUTH 90
#define WEST 180

typedef struct s_win
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	char				*img_data;
	int					bpp; //TODO: wtf?
	int					size_line;
	int					endian;
}						t_win;

typedef struct s_key_params
{
	t_win				*win;
	t_map				*map;
}						t_key_params;

void	ft_init_keymap(t_key_params *params);

#endif
