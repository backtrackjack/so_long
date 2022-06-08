/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 00:10:55 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/07 12:52:09 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdlib.h>

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

	t_sprite	*spr[5];
}	t_game;

int		pos_eq(t_pos pos1, t_pos pos2);

#endif
