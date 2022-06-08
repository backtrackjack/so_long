/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:58:25 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/07 13:00:23 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include <fcntl.h>
#include "my_mlx.h"
#include "so_long.h"
#include "get_next_line.h"

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
		}
		mlx_destroy_window(game->mlx, game->mlx_win);
	}
	free(game);
}

void	exit_w_msg(int status, char *msg, t_game *game)
{
	write(1, msg, ft_strlen(msg));
	free_game(game);
	game = NULL;
	exit(status);
}

char	*nullify_nl(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\n')
			str[i] = '\0';
	}
	return (str);
}

void	set_map(char *path, t_game *game)
{
	char	**temp;
	int		file;

	game->map = malloc(sizeof(t_map));
	if (!game->map)
		exit_w_msg(1, "Could not malloc map", game);
	ft_bzero(game->map, sizeof(t_map));
	game->map->height = 0;
	temp = game->map->layout;
	file = open(path, O_RDONLY);
	if (file == -1)
		exit_w_msg(1, "Invalid map name, try \"./so_long default\"", game);
	*temp = nullify_nl(get_next_line(file));
	while (*temp)
	{
		game->map->layout[game->map->height] = *temp++;
		game->map->height++;
		if (game->map->height - 1 != 0
			&& ft_strlen(game->map->layout[game->map->height - 1])
			!= game->map->width)
			exit_w_msg(1, "Map is not rectangular", game);
		game->map->width = ft_strlen(game->map->layout[game->map->height - 1]);
		*temp = nullify_nl(get_next_line(file));
	}
	close(file);
}

void	sprinit(t_game *game)
{
	t_sprite	**spr;
	int			i;
		 
	i = 0;
	spr = game->spr;
	while (i < 5)
	{
		spr[i] = malloc(sizeof(t_sprite));
		if (spr[i] == NULL)
			exit_w_msg(1, "Could not allocate sprite", game);
		ft_bzero(spr[i], sizeof(t_sprite));
		spr[i]->img = mlx_xpm_file_to_image(game->mlx,
				"img/wall.XPM", &spr[i]->width, &spr[i]->height);
		i++;
	}
}

t_game	*init_game(char *map_name)
{
	t_game	*game;
	void	*mlx;
	void	*mlx_win;

	game = malloc(sizeof(t_game));
	if (game == NULL)
		exit_w_msg(1, "Could not allocate game obj", game);
	ft_bzero(game, sizeof(t_game));
	set_map(ft_strjoin(ft_strjoin("maps/", map_name), ".ber"), game);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx,
			game->map->width * 32, game->map->height * 32, map_name);
	*game = (t_game){game->map, mlx, mlx_win, {NULL}};
	sprinit(game);
	return (game);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac < 2)
		game = init_game("default");
	else
		game = init_game(av[1]);
	mlx_hook(game->mlx_win, 17, 0, (void *)exit, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->spr[0]->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->spr[0]->img, 0, 32);
	mlx_loop(game->mlx);
	return (0);
}
