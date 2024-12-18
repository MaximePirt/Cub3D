#include "cube.h"

void	draw_minimap_rays(t_map *map, t_image *image, int zoom)
{
	t_vector2	start;
	t_vector2	end;
	int			i;
	double		xy;
	double		angle;
	t_ray		*ray;

	xy = (MINIMAP_RENDER_DISTANCE / 2) * zoom;
	start = ft_vector2(xy, xy);
	draw_circle(image, start, zoom / 4, HEX_BLUE);
	if (!map->rays)
		return;
	ray = map->rays;
	i = 0;
	while (i < RAYS_COUNT && ray)
	{
		angle = (map->player.dir - (FOV / 2) + (i * (FOV / RAYS_COUNT))) * M_PI / 180;
		end = ft_vector2(
				start.x + cos(angle) * ray->distance * zoom,
				start.y + sin(angle) * ray->distance * zoom
		);

		ft_draw_line(image, ft_line(start, end, HEX_RED, 1));
		ray = ray->next;
		i++;
	}
}

void	draw_minimap_player(t_image *image, int zoom)
{
	int xy;

	xy = (MINIMAP_RENDER_DISTANCE / 2) * zoom;
	draw_circle(image,
				ft_vector2(xy, xy),
				zoom / 4,
				HEX_RED
	);
}

t_image	*draw_minimap(t_map *map, void *mlx_ptr, int zoom)
{
	t_image	*image;
	int		i;
	int		j;
	double		start_x, start_y;
	double		end_x, end_y;
	double		offset_x, offset_y;

	image = ft_init_image(mlx_ptr, MINIMAP_RENDER_DISTANCE * zoom, MINIMAP_RENDER_DISTANCE * zoom);
	if (!image)
		return (NULL);

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
			offset_x = (i - start_x) * zoom;
			offset_y = (j - start_y) * zoom;
			if (i >= 0 && i < map->size_x && j >= 0 && j < map->size_y)
			{
				if (map->blocks[j][i].type == WALL)
					draw_square(image, ft_vector2(offset_x, offset_y), zoom, HEX_BLACK);
				else
					draw_square(image, ft_vector2(offset_x, offset_y), zoom, HEX_WHITE);
			}
			else
				draw_square(image, ft_vector2(offset_x, offset_y), zoom, HEX_BLACK);
			i++;
		}
		j++;
	}
	draw_minimap_player(image, zoom);
	draw_minimap_rays(map, image, zoom);
	return (image);
}
