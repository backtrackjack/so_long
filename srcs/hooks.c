#include "so_long.h"
#include <stdio.h>

// w 13
// a 0
// s 2
// d 1
// esc 53

// void	move(t_game *g, int dir)
// {

// }

void	*w_handle(t_game *g)
{
	exit_w_msg(1, "\nExiting", g);
	return (NULL);
}

int	handle(int keycode, t_game *g)
{
	// if (keycode == 13)
	// 	move(g, 1);
	// if (keycode == 0)
	// 	move(g, 2);
	// if (keycode == 2)
	// 	move(g, 3);
	// if (keycode == 1)
	// 	move(g, 4);
	if (keycode == 53)
		w_handle(g);
	return (0);
}

void	hook_the_things(t_game *g)
{
	mlx_key_hook(g->mlx_win, handle, g);
	mlx_hook(g->mlx_win, 17, 0L, (void *)w_handle, g);
}