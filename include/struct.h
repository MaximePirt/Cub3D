
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

typedef struct t_textures
{
	void				*wall_north;
	void				*wall_south;
	void				*wall_east;
	void				*wall_west;
	void				*door;
}						t_textures;

typedef struct s_map
{
	t_block				**map;
	t_player 			player;
	t_textures			textures;
	int					size_x;
	int					size_y;
}						t_map;

#endif