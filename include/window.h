#ifndef WINDOW_H
#define WINDOW_H

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

typedef struct s_win
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	char				*img_data;
	int					img_size;
	int					bpp;
}						t_win;

typedef struct s_key_params
{
	t_win				*win;
	t_map				*map;
}						t_key_params;

void	ft_init_keymap(t_win *win, t_map *map);

#endif
