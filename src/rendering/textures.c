/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2024/12/01 06:13:17 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	filling_mlx_data(t_image *image, void *mlx_ptr)
{
	image->img_ptr = mlx_xpm_file_to_image(mlx_ptr, image->path, &image->width,
			&image->height);
	if (!image->img_ptr)
	{
		ft_fprintf(STDERR_FILENO, "Error: loading texture failed\n");
		return (1);
	}
	image->img_data = mlx_get_data_addr(image->img_ptr, &image->bpp,
			&image->size_line, &image->endian);
	if (!image->img_data)
	{
		ft_fprintf(STDERR_FILENO, "Error: getting texture data failed\n");
		return (1);
	}
	return (0);
}

/**
 * @brief Check paths and load the texture
 * @param image the image
 * @param path the path
 * @param mlx_ptr the mlx ptr
 */
int	load_texture(t_image *image, char *path, void *mlx_ptr)
{
	char	**tmp;
	int		fd;

	tmp = ft_split(path, " \n");
	if (!tmp || !tmp[1])
		return (1);
	image->path = ft_strdup(tmp[1]);
	fd = open(image->path, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "Error: invalid texture path\n");
		return (1);
	}
	close(fd);
	ft_tabfree(tmp);
	if (filling_mlx_data(image, mlx_ptr))
		return (1);
	return (0);
}

int	str_is_charset(char *str, char *charset)
{
	int	i;
	int	j;
	int	valide;

	i = 0;
	while (str[i])
	{
		j = 0;
		valide = 0;
		while (charset[j])
		{
			if (str[i] == charset[j])
				valide = 1;
			j++;
		}
		if (!valide)
			return (1);
		i++;
	}
	return (0);
}

int	error_in_rgb(char **tmp, int i, int **converted, char *value)
{
	if (str_is_charset(tmp[i], "0123456789,") || ft_str_count_char(value,
			',') != 2 || ft_count_words(value, "\n") != 1)
	{
		ft_fprintf(STDERR_FILENO, "Error: Check your RGB settings\n");
		return (1);
	}
	(*converted)[i] = ft_atoi(tmp[i]);
	if ((*converted)[i] < 0 || (*converted)[i] > 255)
	{
		ft_fprintf(STDERR_FILENO, "Error: invalid color value\n");
		return (1);
	}
	return (0);
}

int	fill_rgb_texture(t_rgb *items, char *value)
{
	char	**tmp;
	int		i;
	int		*converted;

	i = 1;
	tmp = ft_split(value, " ,\n");
	if (!tmp || !tmp[1] || !tmp[2] || !tmp[3])
		return (1);
	converted = malloc(5 * sizeof(int));
	while (tmp[i])
	{
		if (error_in_rgb(tmp, i, &converted, value))
			return (1);
		i++;
	}
	items->r = converted[1];
	items->g = converted[2];
	items->b = converted[3];
	ft_tabfree(tmp);
	free(converted);
	return (0);
}
