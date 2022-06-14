/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:24:51 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/14 17:13:15 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	finish_game(t_game *g)
{
	g->moves++;
	display_moves(g);
	exit_w_msg(1, "Finished", g);
}

int	collect(t_game *g, t_pos t)
{
	int	i;

	i = write(1, "\a", 1);
	i++;
	mlx_put_image_to_window(g->mlx, g->mlx_win,
		g->spr[4]->img, t.x * 32, t.y * 32);
	g->map->layout[t.y][t.x] = '0';
	g->score++;
	return (1);
}

void	*close_game(t_game *g)
{
	exit_w_msg(1, "Exiting", g);
	return (0);
}

int	handle(int keycode, t_game *g)
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

void	hook_the_things(t_game *g)
{
	mlx_key_hook(g->mlx_win, handle, g);
	mlx_hook(g->mlx_win, 17, 0L, (void *)close_game, g);
}
