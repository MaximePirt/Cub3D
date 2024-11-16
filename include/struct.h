
#ifndef STRUCT_H
#define STRUCT_H

typedef enum s_block_type
{
	VOID,
	FLOOR,
	WALL,
	DOOR
}	t_block_type;

typedef struct s_player
{
	double				x;
	double				y;
	double				dir;
}						t_player;

typedef struct s_block
{
	t_block_type 		type;
	int					status;
}						t_block;

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

typedef struct t_textures
{
	t_image				*wall_north;
	t_image				*wall_south;
	t_image				*wall_east;
	t_image				*wall_west;
	t_image				*door;
}						t_textures;

typedef struct s_map
{
	t_block				**blocks;
	t_player 			player;
	t_textures			*textures;
	int					size_x;
	int					size_y;
}						t_map;

#endif