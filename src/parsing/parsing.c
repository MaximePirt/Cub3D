#include "cube.h"

int	check_name(char *file)
{
    int		i;
    char	str[4];

    if (!file)
        return (-1);
    str[0] = '.';
    str[1] = 'b';
    str[2] = 'e';
    str[3] = 'r';
    i = 0;
    while (file[i])
        i++;
    if (i <= 4)
        return (-1);
    i = ft_strncmp_end(file, str, 4);
    if (i == -1)
        return (-1);
    return (0);
}

static int	how_many_line(char *file)
{
    int		fd;
    int		i;
    char	*str;

    i = 0;
    fd = open(file, O_RDONLY);
    if (fd == -1)
        exit_func(0, NULL, NULL, 2);
    str = get_next_line(fd);
    while (str)
    {
        i++;
        free(str);
        str = NULL;
        str = get_next_line(fd);
    }
    free(str);
    str = NULL;
    close(fd);
    return (i);
}

void	oh_problems(t_map *map, char *str, int i, int fd)
{
    if ((i == map->size_y && ft_strlen(str) != map->line_len - 1) || (i > 1
            && i != map->size_y && ft_strlen(str) != map->line_len)
        || str[0] != '1' || str[map->line_len - 2] != '1' || (i == map->size_y
            && ft_check_only(str, '1') == -1) || (i == 1 && ft_check_only(str,
                '1') == -1) || map->size_y < 3 || ((i > 1 && i != map->size_y)
            && ft_check_only_string(str, "10ECPGKN\n") == -1))
    {
        free(str);
        str = NULL;
        exit_func(fd, map, NULL, 8);
    }
}

void	check_size(t_map *map)
{
    char	*str;
    int		fd;
    int		i;

    i = 1;
    fd = open(map->file_name, O_RDONLY);
    if (fd == -1)
        exit_func(0, map, NULL, 2);
    str = get_next_line(fd);
    if (!str)
        exit_func(fd, map, NULL, 9);
    map->line_len = ft_strlen(str);
    map->size_x = map->line_len;
    map->size_y = how_many_line(map->file_name);
    while (str && str[0] != 0)
    {
        oh_problems(map, str, i++, fd);
        if (ft_check(str, '\0'))
            break ;
        free(str);
        str = get_next_line(fd);
    }
    free(str);
    close(fd);
    return ;
}