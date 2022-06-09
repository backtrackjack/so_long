/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:20:37 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/09 15:53:00 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_the_thing(t_game *g, int (*f)(void*, void*, void*, int, int))
{
	int	i[2];

	i[0] = -1;
	while (++i[0] < g->map->height)
	{
		i[1] = -1;
		while (++i[1] < g->map->width)
		{
			if (g->map->layout[i[0]][i[1]] == '1')
				f(g->mlx, g->mlx_win, g->spr[0]->img, i[1] * 32, i[0] * 32);
			else if (g->map->layout[i[0]][i[1]] == 'E')
				f(g->mlx, g->mlx_win, g->spr[1]->img, i[1] * 32, i[0] * 32);
			else if (g->map->layout[i[0]][i[1]] == 'C'
					|| g->map->layout[i[0]][i[1]] == 'P')
			{
				f(g->mlx, g->mlx_win, g->spr[4]->img, i[1] * 32, i[0] * 32);
				if (g->map->layout[i[0]][i[1]] == 'C')
					f(g->mlx, g->mlx_win, g->spr[2]->img, i[1] * 32, i[0] * 32);
				else
					f(g->mlx, g->mlx_win, g->spr[3]->img, i[1] * 32, i[0] * 32);
			}
			else
				f(g->mlx, g->mlx_win, g->spr[4]->img, i[1] * 32, i[0] * 32);
		}
	}
}
