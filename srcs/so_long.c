/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:58:25 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/08 13:05:42 by jsellars         ###   ########.fr       */
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
	mlx_hook(game->mlx_win, 17, 0, (void *)exit, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->spr[0]->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->spr[1]->img, 0, 32);
	exit_w_msg(1, "test", game);
	mlx_loop(game->mlx);
	return (0);
}
