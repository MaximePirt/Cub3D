#include "cube.h"


static void	draw_minimap_rays(t_image *img, t_map *map, int zoom)
{
	t_vector2	start;
	t_vector2	end;
	int			i;
	double		xy;
	double		angle;
	t_ray		*ray;

	if (!map->rays)
		return;
	xy = (MINIMAP_RENDER_DISTANCE / 2) * zoom;
	start = ft_vector2(xy, xy);
	ray = map->rays;
	i = 0;
	while (i < RAYS_COUNT && ray)
	{
		angle = (map->player.dir + (i * (FOV / (double)RAYS_COUNT)) - (FOV / 2)) * M_PI / 180.0;
		end = ft_vector2(
				start.x + cos(angle) * ray->distance * zoom,
				start.y + sin(angle) * ray->distance * zoom
		);
		ft_draw_line(img, ft_line(start, end, HEX_RED, 1));
		ray = ray->next;
		i++;
	}
}

static void	draw_minimap_player(t_image *img, int zoom)
{
	int xy;

	xy = (MINIMAP_RENDER_DISTANCE / 2) * zoom;
	draw_circle(img,
				ft_vector2(xy, xy),
				zoom / 4,
				HEX_RED
	);
}

void	draw_minimap(t_map *map)
{
	int		i;
	int		j;
	double		start_x, start_y;
	double		end_x, end_y;
	double		offset_x, offset_y;

	start_x = map->player.x - (MINIMAP_RENDER_DISTANCE / 2);
	start_y = map->player.y - (MINIMAP_RENDER_DISTANCE / 2);
	end_x = start_x + MINIMAP_RENDER_DISTANCE;
	end_y = start_y + MINIMAP_RENDER_DISTANCE;
	j = start_y;
	while (j < end_y)
	{
		i = start_x;
		while (i < end_x)
		{
			offset_x = (i - start_x) * map->minimap->zoom;
			offset_y = (j - start_y) * map->minimap->zoom;
			if (i >= 0 && i < map->size_x && j >= 0 && j < map->size_y)
			{
				if (map->blocks[j][i].type == WALL)
					draw_square(map->minimap->image, ft_vector2(offset_x, offset_y), map->minimap->zoom, HEX_BLACK);
				else if (map->blocks[j][i].type == DOOR)
					draw_square(map->minimap->image, ft_vector2(offset_x, offset_y), map->minimap->zoom, HEX_CYAN);
				else
					draw_square(map->minimap->image, ft_vector2(offset_x, offset_y), map->minimap->zoom, HEX_WHITE);
			}
			else
				draw_square(map->minimap->image, ft_vector2(offset_x, offset_y), map->minimap->zoom, HEX_BLACK);
			i++;
		}
		j++;
	}
	draw_minimap_player(map->minimap->image, map->minimap->zoom);
	draw_minimap_rays(map->minimap->image, map, map->minimap->zoom);
}
