/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:58:25 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/14 17:48:58 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "so_long.h"

void	get_c_count(t_game *g)
{
	char	**m;
	int		i;
	int		j;

	m = g->map->layout;
	i = 0;
	j = 0;
	while (i < g->map->height)
	{
		while (j < g->map->width)
		{
			if (m[i][j] == 'C')
				g->c_count++;
			j++;
		}
		j = 0;
		i++;
	}
}

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
