#include "cube.h"

//void	fill_struc_compo(t_map *map, char c, int x, int y)
//{
//	if (c == 'C')
//	{
//		map->component_data->hm_component++;
//		ft_lstadd_back_cmpnt(&map->component_data->lst_component,
//			ft_lstnew_cmpnt(map->component_data->lst_component, x, y));
//	}
//	else if (c == 'P')
//	{
//		map->player_data.player++;
//		map->player_data.x = y;
//		map->player_data.y = x;
//	}
//	else if (c == 'E')
//	{
//		map->exit_data.exit++;
//		map->exit_data.x = x;
//		map->exit_data.y = y;
//	}
//	else
//		fill_enemy_and_gun(map, c, x, y);
//	return ;
//}
//
//void	flood_fill(t_map *map, int x, int y)
//{
//	if (!map->map_fill[x][y] || x < 0 || x >= map->size_y || y < 0
//		|| y >= map->size_x || map->map_fill[x][y] == '1'
//		|| map->map_fill[x][y] == 'F' || map->map_fill[x][y] == 'K'
//		|| map->map_fill[x][y] == 'N')
//		return ;
//	fill_struc_compo(map, map->map_fill[x][y], x, y);
//	map->map_fill[x][y] = 'F';
//	flood_fill(map, x - 1, y);
//	flood_fill(map, x + 1, y);
//	flood_fill(map, x, y - 1);
//	flood_fill(map, x, y + 1);
//	if (map->player_data.player > 1 || map->exit_data.exit > 1
//		|| map->gun_data.hm_gun > 1)
//		exit_func(0, map, NULL, 5);
//	return ;
//}
//
//void	where_start_fill(t_map *map)
//{
//	int	i;
//	int	j;
//
//    i = 0;
//    j = 0;
//	while (m)
//
//}
//
//void	check_min_inputs(t_map *map)
//{
//	int	i;
//	int	j;
//	int	k;
//	int	l;
//
//	i = ft_check_in_tab(map->map, 'E');
//	j = ft_check_in_tab(map->map, 'C');
//	k = ft_check_in_tab(map->map, 'P');
//	l = ft_check_in_tab(map->map, 'G');
//	if (i == -1 || j == -1 || k == -1 || l == -1)
//		exit_func(0, map, NULL, 5);
//}
//
int	*preptoflood(t_map *map)
{
	int		component;
	int		i;

	i = 0;
	where_start_fill(map);
	flood_fill(map, map->col, map->line);
//	if (component != map->component_data->hm_component + map->player_data.player
//		+ map->exit_data.exit + map->gun_data.hm_gun
//		|| map->component_data->hm_component < 1)
//		exit_func(0, map, NULL, 5);
	return (map);
}