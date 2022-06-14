/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:38:20 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/14 16:38:28 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_pos	get_p_pos(char **map)
{
	int		i;
	int		j;
	t_pos	pos;

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

void	pos_swap(t_game *g, t_pos pos, char dir)
{
	char	*tile;
	char	temp;

	temp = g->map->layout[pos.y][pos.x];
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

void	move(t_game *g, char dir)
{
	t_pos	pos;

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

int	check_tile(t_game *g, t_pos pos, char dir)
{
	t_pos	t;
	char	**map;

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
