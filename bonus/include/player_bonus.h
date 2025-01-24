#ifndef PLAYER_H
#define PLAYER_H


int		player_move_forward(t_map *map);
int		player_move_backward(t_map *map);
int		player_move_left(t_map *map);
int		player_move_right(t_map *map);
void	update_player_old_pos(t_map *map);

#endif