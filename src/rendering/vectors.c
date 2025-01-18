#include "cube.h"

t_vector2	ft_vector2(double x, double y)
{
	t_vector2	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_line	ft_line(t_vector2 start, t_vector2 end, int color, int width)
{
	t_line	line;

	line.start = start;
	line.end = end;
	line.color = color;
	line.width = width;
	return (line);
}
