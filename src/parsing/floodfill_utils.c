#include "cube.h"

void	copy_map_to_mapfill(t_map *map)
{
    size_t	i;

    map->map_fill = ft_calloc(sizeof(char *), (map->size_y + 1));
    if (!map->map_fill)
        exit_func(0, map, NULL, 3);
    i = 0;
    while (map->map[i])
    {
        map->map_fill[i] = ft_strdup(map->map[i]);
        map->map_fill[i][map->size_x - 1] = '\0';
        i++;
    }
    return ;
}

void	clean_flood(t_map *map)
{
    t_componentlst	*tmp;

    free_tab(map->map_fill);
    tmp = map->component_data->lst_component;
    map->component_data->lst_component = map->component_data->lst_component->next;
    free(tmp);
    map->map_fill = NULL;
    tmp = NULL;
}

int	hm_compo(char **tab)
{
    int	i;
    int	a;
    int	compo;

    i = 0;
    a = 0;
    compo = 0;
    while (tab[a])
    {
        while (tab[a][i])
        {
            if (tab[a][i] != '1' && tab[a][i] != '0' && tab[a][i] != 'C'
                && tab[a][i] != 'E' && tab[a][i] != 'P' && tab[a][i] != 'G'
                && tab[a][i] != 'K' && tab[a][i] != 'N' && tab[a][i] != '\n')
                exit_func(0, NULL, tab, 4);
            if (tab[a][i] == 'C' || tab[a][i] == 'E' || tab[a][i] == 'P'
                || tab[a][i] == 'G')
                compo++;
            i++;
        }
        i = 0;
        a++;
    }
    return (compo);
}