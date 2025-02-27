/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:47:24 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/26 18:59:18 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_BONUS_H
# define CUBE_BONUS_H

# include "../../libft/include/colors.h"
# include "../../libft/include/libft.h"
# include "../../minilibx/mlx.h"
# include "parsing_bonus.h"
# include "player_bonus.h"
# include "struct_bonus.h"
# include "window_bonus.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

// Memory allocation

t_map		*ft_init_map(int size_x, int size_y);
t_block		*ft_init_block(void);
t_win		*ft_init_window(void);
t_textures	*ft_init_textures(void);
t_image		*ft_init_image(void *mlx_ptr, int width, int height);
t_ray		*ft_init_rays(void);

// Memory free

int			ft_free_program(t_key_params *params);
void		free_parse_map(t_parse_map *map);
void		*ft_free_rays(t_ray *rays);
void		*ft_free_map(t_block **blocks, int size_y);
void		ft_free_textures(t_win *win, t_textures *textures);
void		free_images(char **images);

// Game loop

int			game_loop(t_key_params *params);

// Key/Mouse actions

int			action_key(int keycode, t_key_params *params);
int			action_mouse_key(int button, int x, int y, t_key_params *params);

// Player actions

int			player_move_forward(t_map *map);
int			player_move_backward(t_map *map);
int			player_move_left(t_map *map);
int			player_move_right(t_map *map);
int			player_look_left(t_map *map);
int			player_look_right(t_map *map);
int			door_interact(t_map *map);

// Rendering

void		refresh(t_win *win, t_map *map);
int			fill_rgb_texture(t_rgb *items, char *value);
int			load_texture(t_image *image, char *path, void *mlx_ptr);
void		ft_draw_pixel_on_image(t_image *image, t_vector2 pos, int color);
void		ft_draw_pixel_on_screen(t_win *win, t_vector2 pos, int color);
void		ft_draw_line(t_image *img, t_line line);
int			get_pixel_color(t_image *texture, t_vector2 pos);
void		set_pixel_color(t_win *win, t_vector2 pos, int color);

void		draw_square(t_image *img, t_vector2 pos, int size, int color);
void		draw_circle(t_image *img, t_vector2 pos, int radius, int color);
void		draw_rectangle(t_win *win, t_vector2 pos, t_vector2 width_eight,
				int color);

// Images tools

void		paste_image_on_screen(t_win *win, t_image *image, t_vector2 pos);
void		ft_fill_image(t_image *img, int color);

// Minimap

void		draw_minimap(t_map *map);

// Vectors
t_vector2	ft_vector2(double x, double y);
t_line		ft_line(t_vector2 start, t_vector2 end, int color, int width);

// Raycast
int			give_all_rays(t_map *map);

#endif
