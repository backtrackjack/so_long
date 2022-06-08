/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 00:10:55 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/08 15:31:56 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "mlx.h"

#define MAX_MAP_HEIGHT 75
#define MAX_MAP_WIDTH 100


typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_player
{
	t_pos	pos;
	int		score;
}	t_player;

typedef struct s_map
{
	char *layout[MAX_MAP_HEIGHT];
	int width;
	int height;
} t_map;

typedef struct s_sprite
{
	void	*img;
	int		width;
	int		height;
}	t_sprite;

typedef struct s_game
{
	t_map		*map;
	//t_player	*player;
	void		*mlx;
	void		*mlx_win;

	t_sprite	*spr[6];
}	t_game;

int		pos_eq(t_pos pos1, t_pos pos2);
void	ft_bzero(void *s, size_t n);
void	free_game(t_game *game);
void	exit_w_msg(int status, char *msg, t_game *game);
t_game	*init_game(char *map_name);
int		check_map(t_map *map);

#endif
