#include "cube.h"

int parsing_map(char *filename)
{
  if (check_name(filename) == -1)
  {
    ft_fprintf(2, "Error\n");
    return (1);
  }

  return (0);
}
