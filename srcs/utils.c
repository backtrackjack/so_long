/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:11:35 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/14 19:33:10 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*c;
	size_t			i;

	c = s;
	i = 0;
	while (i < n)
	{
		c[i] = '\0';
		i++;
	}
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	while (game->map->height--)
	{
		free(game->map->layout[game->map->height]);
		game->map->layout[game->map->height] = NULL;
	}
	free(game->map);
	game->map = NULL;
	if (game->mlx && game->mlx_win)
	{
		while (game->spr[i])
		{
			if (game->spr[i]->img)
				mlx_destroy_image(game->mlx, game->spr[i]->img);
			free(game->spr[i]);
			game->spr[i] = NULL;
			i++;
		}
		mlx_destroy_window(game->mlx, game->mlx_win);
	}
	free(game);
}

void	exit_w_msg(int status, char *msg, t_game *game)
{
	int	i;

	i = write(1, msg, ft_strlen(msg));
	i++;
	if (game)
	{
		free_game(game);
		game->mlx = NULL;
		game->mlx_win = NULL;
		game = NULL;
	}
	exit(status);
}

int	check_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < map->width)
	{
		if (map->layout[map->height - 1][x] != '1'
			|| map->layout[0][x] != '1')
			return (1);
		x++;
	}
	while (y < map->height)
	{
		if (map->layout[y][map->width - 1] != '1'
			|| map->layout[y][0] != '1')
			return (1);
		y++;
	}
	return (0);
}
