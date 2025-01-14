
#ifndef STRUCT_H
#define STRUCT_H

typedef enum s_block_type
{
	VOID,
	FLOOR,
	WALL,
	DOOR,
	FILL,
	NOTHING
}	t_block_type;

typedef struct s_vector2
{
	double				x;
	double				y;
}						t_vector2;

typedef struct t_image
{
	char 				*path;
	void				*img_ptr;
	char				*img_data;
	int					bpp;
	int					size_line;
	int					endian;
	int 				width;
	int 				height;
}						t_image;

typedef struct s_player
{
	double				x;
	double				y;
	double				old_x;
	double				old_y;
	double				dir;
	double 				old_dir;
	t_image				*texture;
}						t_player;

typedef struct s_block
{
	t_block_type 		type;
	int					status;
}						t_block;

typedef	struct	s_rgb
{
	int				r;
	int				g;
	int				b;
}				t_rgb;

typedef struct s_textures
{
	t_image				*wall_north;
	t_image				*wall_south;
	t_image				*wall_east;
	t_image				*wall_west;
	t_image				*door;
	t_image 			*right_hand;
	t_rgb				floor;
	t_rgb				ceiling;
}						t_textures;

typedef struct s_ray
{
	double				distance;
	int					id;
	double				toucher_x;
	struct s_ray		*next;
	struct s_ray		*prev;
}						t_ray;

typedef struct s_map
{
	t_block				**blocks;
	t_player 			player;
	t_textures			*textures;
	int					size_x;
	int					size_y;
	t_ray				*rays;
	int 				minimap_zoom;
	int 				mouse_lock;
}						t_map;

typedef struct s_parse_map
{
  	int					blocks_len;
    char				*blocks;
    struct s_parse_map	*next;
}						t_parse_map;

typedef	struct s_stack
{
	int					x;
	int					y;
}						t_stack;

typedef struct s_line
{
	t_vector2	start;
	t_vector2	end;
	int			color;
	int 		width;
}						t_line;

#endif