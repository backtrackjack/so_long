/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:11:50 by jsellars          #+#    #+#             */
/*   Updated: 2022/06/14 10:23:41 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

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

char	*fl_strjoin(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}

void	set_map(char *path, t_game *game)
{
	char	**temp;
	int		file;

	game->map = malloc(sizeof(t_map));
	if (!game->map)
		exit_w_msg(1, "Error\nCould not malloc map", game);
	ft_bzero(game->map, sizeof(t_map));
	game->map->height = 0;
	temp = game->map->layout;
	file = open(path, O_RDONLY);
	if (file == -1)
		exit_w_msg(1, "Error\nInvalid map name, try \"./so_long default\"", game);
	*temp = nullify_nl(get_next_line(file));
	while (*temp)
	{
		game->map->layout[game->map->height] = *temp++;
		game->map->height++;
		if (game->map->height - 1 != 0
			&& ft_strlen(game->map->layout[game->map->height - 1])
			!= game->map->width)
			exit_w_msg(1, "Error\nMap is not rectangular", game);
		game->map->width = ft_strlen(game->map->layout[game->map->height - 1]);
		*temp = nullify_nl(get_next_line(file));
	}
	close(file);
}

void	sprinit(t_game *x)
{
	t_sprite	**s;
	int			i;
	void		*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	i = 0;
	s = x->spr;
	while (i < 5)
	{
		s[i] = malloc(sizeof(t_sprite));
		if (s[i] == NULL)
			exit_w_msg(1, "Error\nCould not allocate sprite", x);
		ft_bzero(s[i], sizeof(t_sprite));
		i++;
	}
	s[0]->img = f(x->mlx, "img/wall.XPM", &s[0]->width, &s[0]->height);
	s[1]->img = f(x->mlx, "img/exit.XPM", &s[1]->width, &s[1]->height);
	s[2]->img = f(x->mlx, "img/item.XPM", &s[2]->width, &s[2]->height);
	s[3]->img = f(x->mlx, "img/player.XPM", &s[3]->width, &s[3]->height);
	s[4]->img = f(x->mlx, "img/empty.XPM", &s[4]->width, &s[4]->height);
	s[5] = NULL;
}

t_game	*init_game(char *map_name)
{
	t_game	*game;
	char	*path;
	void	*mlx;
	void	*mlx_win;

	game = malloc(sizeof(t_game));
	if (game == NULL)
		exit_w_msg(1, "Error\nCould not allocate game obj", game);
	ft_bzero(game, sizeof(t_game));
	path = fl_strjoin(ft_strjoin("maps/", map_name), ".ber");
	set_map(path, game);
	free(path);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx,
			game->map->width * 32, game->map->height * 32, map_name);
	*game = (t_game){game->map, mlx, mlx_win, {NULL}, 0, 0, 0};
	sprinit(game);
	return (game);
}
