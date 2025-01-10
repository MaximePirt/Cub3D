#include "cube.h"

t_ray	*ft_init_rays(void)
{
	t_ray	*head;
	t_ray	*current;
	t_ray	*prev;
	int		i;

	head = NULL;
	prev = NULL;
	i = 0;
	while (i < RAYS_COUNT)
	{
		current = (t_ray *)malloc(sizeof(t_ray));
		if (!current)
		{
			while (head)
			{
				t_ray *temp = head->next;
				free(head);
				head = temp;
			}
			return (NULL);
		}
		current->distance = 1;
		//TODO: Remove id -> i use it only to debug which one i am currently 
		current->id = i;
		current->next = NULL;
		current->prev = prev;
		if (prev)
			prev->next = current;
		else
			head = current;
		prev = current;
		i++;
	}
	return (head);
}
