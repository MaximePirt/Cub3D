/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:47:01 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/25 02:49:45 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_block_type
{
	VOID,
	FLOOR,
	WALL,
	DOOR,
	FILL,
	NOTHING
}						t_block_type;

typedef struct s_vector2
{
	double				x;
	double				y;
}						t_vector2;

typedef struct t_image
{
	char				*path;
	void				*img_ptr;
	char				*img_data;
	int					bpp;
	int					size_line;
	int					endian;
	int					width;
	int					height;
}						t_image;

typedef struct s_player
{
	double				x;
	double				y;
	double				old_x;
	double				old_y;
	double				dir;
	double				old_dir;
	int					hand_animation_pos;
	int					hand_animation_direction;
	t_image				*texture;
}						t_player;

typedef struct s_block
{
	t_block_type		type;
	int					status;
}						t_block;

typedef struct s_rgb
{
	int					r;
	int					g;
	int					b;
}						t_rgb;

typedef struct s_textures
{
	t_image				*wall_north;
	t_image				*wall_south;
	t_image				*wall_east;
	t_image				*wall_west;
	t_image				*door;
	t_image				*right_hand;
	t_rgb				floor;
	t_rgb				ceiling;
}						t_textures;

typedef struct s_ray
{
	double				distance;
	double				angle;
	int					side;
	double				x_axis;
	t_block_type		type;
	struct s_ray		*next;
	struct s_ray		*prev;
}						t_ray;

typedef struct s_calcul_ray
{
	double				add_angle;
	double				angle;
	double				ray_dirx;
	double				ray_diry;
	double				posx;
	double				posy;
	int					mapx;
	int					mapy;
	double				deltadistx;
	double				deltadisty;
	int					hit;
	int					side;
	double				perpwalldist;
	int					stepx;
	int					stepy;
	double				sidedistx;
	double				sidedisty;
}						t_calcul_ray;

typedef struct s_calcul_process
{
	double				ray_angle;
	double				add_angle;
	int					height;
	int					width;
	t_vector2			pos;
}						t_calcul_process;

typedef struct s_minimap
{
	int					zoom;
	t_image				*image;
}						t_minimap;

typedef struct s_map
{
	t_block				**blocks;
	t_player			player;
	t_textures			*textures;
	int					size_x;
	int					size_y;
	t_ray				*rays;
	t_minimap			*minimap;
	int					mouse_lock;
}						t_map;

typedef struct s_parse_map
{
	int					blocks_len;
	char				*blocks;
	struct s_parse_map	*next;
}						t_parse_map;

typedef struct s_stack
{
	int					x;
	int					y;
}						t_stack;

typedef struct s_line
{
	t_vector2			start;
	t_vector2			end;
	int					color;
	int					width;
}						t_line;

#endif