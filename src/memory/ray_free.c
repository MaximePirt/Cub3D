#include "cube.h"

void	*ft_free_rays(t_ray *rays)
{
	t_ray	*tmp;

	while (rays)
	{
		tmp = rays;
		rays = rays->next;
		free(tmp);
	}
	return (NULL);
}
