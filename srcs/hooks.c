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
t_pos	get_p_pos(char **map)
{
	int		i;
	int		j;
	t_pos	pos;
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
	}
	return (NULL);
}

void	pos_swap(t_game *g, t_pos pos, char dir)
{
	char	*tile;
	char	temp;

	if (dir == 'u')
		tile = &g->map->layout[pos.y + 1][pos.x];
	if (dir == 'l')
		tile = &g->map->layout[pos.y][pos.x - 1];
	if (dir == 'd')
		tile = &g->map->layout[pos.y - 1][pos.x]
	if (dir == 'r')
		tile = &g->map->layout[pos.y][pos.x + 1];
	
	temp = g->map->layout[pos.y][pos.x];
	*tile = g->map->layout[pos.y][pos.x];
	tem
}

int	collect(t_game *g, t_pos t)
{
	int	i;
	i = write(1, "\a", 1);
	mlx_put_image_to_window(g->mlx, g->mlx_win,
			g->spr[4]->img, t.x * 32, t.y * 32);
	g->score++;
	return (1);
}

int	check_tile(t_game *g, t_pos pos, char dir)
{
	t_pos	t;
	char	**map;

	map = g->map->layout;
	t = pos;
	if (dir == 'u')
		t.y++;
	else if (dir == 'l')
		t.x--;
	else if (dir == 'd')
		t.y--;
	else
		t.x++;
	if (map[t.y][t.x] == '0')
		return (1);
	if (map[t.y][t.x] == 'E')
		finish_game(g);
	if (map[t.y][t.x] == 'C')
		return (collect(g, t));
	return (0);
}

void	move(t_game *g, char dir)
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
}

void	*close_game(t_game *g)
{
	exit_w_msg(1, "Exiting", g);
	return (0);
}

int handle(int keycode, t_game *g)
{
	write(1, ft_itoa(keycode), ft_strlen(ft_itoa(keycode)));
	if (keycode == W)
		move(g, 'u');
	if (keycode == A)
		move(g, 'l');
	if (keycode == S)
		move(g, 'd');
	if (keycode == D)
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
