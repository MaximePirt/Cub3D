#include "cube.h"

int parsing_map(char *filename)
{
  if (check_name(filename))
  {
    ft_fprintf(2, "Error\n");
    return (1);
  }

  return (0);
}
