/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:58:25 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/08 16:00:33 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac < 2)
		game = init_game("default");
	else
		game = init_game(av[1]);
	if (check_map(game->map))
		exit_w_msg(1, "Map not surrounded by walls", game);
	// hook_the_things();
	// display_the_thing();
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->spr[0]->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->spr[2]->img, 0, 32);
	mlx_loop(game->mlx);
	return (0);
}
