#include <mlx.h>
#include "my_mlx.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->addr + (y + data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = colour;
}
