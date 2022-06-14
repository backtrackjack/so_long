/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:58:25 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/14 10:34:37 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	*game;

	game = NULL;
	if (ac != 2)
		exit_w_msg(1, "Error\n./so_long <map_name>", game);
	else
		game = init_game(av[1]);
	if (check_map(game->map))
		exit_w_msg(1, "Error\nMap not surrounded by walls", game);
	hook_the_things(game);
	display_the_thing(game, mlx_put_image_to_window);
	display_moves(game);
	mlx_loop(game->mlx);
	return (0);
}
