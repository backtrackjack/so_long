#include "so_long.h"
#include <stdio.h>

// macos
// w 13
// a 0
// s 2
// d 1
// esc 53

// linux
//  w 119
//  a 97
//  s 115
//  d 100
//  esc 65307
t_pos get_p_pos(char **map)
{
	int i;
	int j;
	t_pos pos;
	pos.x = -1;
	pos.y = -1;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				pos.x = j;
				pos.y = i;
				return (pos);
			}
			j++;
		}
		i++;
	}
	return (pos);
}

void finish_game(t_game *g)
{
	g->moves++;
	display_moves(g);
	exit_w_msg(1, "Finished", g);
}

void pos_swap(t_game *g, t_pos pos, char dir)
{
	char *tile;
	char temp = g->map->layout[pos.y][pos.x];

	if (dir == 'u')
		tile = &g->map->layout[pos.y - 1][pos.x];
	else if (dir == 'l')
		tile = &g->map->layout[pos.y][pos.x - 1];
	else if (dir == 'd')
		tile = &g->map->layout[pos.y + 1][pos.x];
	else
		tile = &g->map->layout[pos.y][pos.x + 1];
	g->map->layout[pos.y][pos.x] = *tile;
	g->moves++;
	*tile = temp;
}

int collect(t_game *g, t_pos t)
{
	int i;
	i = write(1, "\a", 1);
	i++;
	mlx_put_image_to_window(g->mlx, g->mlx_win,
							g->spr[4]->img, t.x * 32, t.y * 32);
	g->map->layout[t.y][t.x] = '0';
	return (1);
}

int check_tile(t_game *g, t_pos pos, char dir)
{
	t_pos t;
	char **map;

	map = g->map->layout;
	t = pos;
	if (dir == 'u')
		t.y--;
	else if (dir == 'l')
		t.x--;
	else if (dir == 'd')
		t.y++;
	else
		t.x++;
	if (map[t.y][t.x] == '0')
		return (1);
	if (map[t.y][t.x] == 'E' && g->score == g->c_count)
		finish_game(g);
	if (map[t.y][t.x] == 'C')
		return (collect(g, t));
	return (0);
}

void move(t_game *g, char dir)
{
	t_pos pos;

	pos = get_p_pos(g->map->layout);
	if (dir == 'u' && check_tile(g, pos, 'u'))
		pos_swap(g, pos, 'u');
	if (dir == 'l' && check_tile(g, pos, 'l'))
		pos_swap(g, pos, 'l');
	if (dir == 'd' && check_tile(g, pos, 'd'))
		pos_swap(g, pos, 'd');
	if (dir == 'r' && check_tile(g, pos, 'r'))
		pos_swap(g, pos, 'r');
	display_the_thing(g, mlx_put_image_to_window);
	display_moves(g);
}

void *close_game(t_game *g)
{
	exit_w_msg(1, "Exiting", g);
	return (0);
}

int handle(int keycode, t_game *g)
{
	if (keycode == MOVE_UP)
		move(g, 'u');
	if (keycode == MOVE_LEFT)
		move(g, 'l');
	if (keycode == MOVE_DOWN)
		move(g, 'd');
	if (keycode == MOVE_RIGHT)
		move(g, 'r');
	if (keycode == ESC)
		close_game(g);
	return (g->map->height);
}

void hook_the_things(t_game *g)
{
	mlx_key_hook(g->mlx_win, handle, g);
	mlx_hook(g->mlx_win, 17, 0L, (void *)close_game, g);
}
