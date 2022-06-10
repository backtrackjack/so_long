#include "so_long.h"
#include <stdio.h>

// macos
// w 13
// a 0
// s 2
// d 1
// esc 53

// linux
//  w 119
//  a 97
//  s 115
//  d 100
//  esc 65307
/*
 *t_pos	get_p_pos(char **map)
 *{
 *    int		i;
 *    int		j;
 *    t_pos	pos;
 *    i = 0;
 *    while (map[i])
 *    {
 *        j = 0;
 *        while (map[i][j])
 *        {
 *            if (map[i][j] == 'P')
 *            {
 *                pos.x = j;
 *                pos.y = i;
 *                return (pos);
 *            }
 *            j++;
 *        }
 *    }
 *}
 */

/*
 *int	valid(t_game g, char c)
 *{
 *    if (c == '0')
 *        return (1);
 *    if (c == 'E')
 *        [>finish_game(g);<]
 *    if (c == 'C')
 *        [>collect(g);<]
 *    return (0);
 *}
 */

/*
 *int	check_tile(t_game *g, t_pos pos, char dir)
 *{
 *    if (dir == 'u' && valid(g, g->map->layout[pos.y + 1][pos.x]))
 *
 *    
 *}
 */

/*
 *void	move(t_game *g, int dir)
 *{
 *    t_pos pos;
 *
 *    pos = get_p_pos(g->map->layout);
 *    if (dir == 1 && check_tile(g, pos, 'u'))
 *        pos_swap(g, pos, 'u');
 *    if (dir == 2 && check_tile(g, pos, 'l'))
 *        pos_swap(g, pos, 'l');
 *    if (dir == 3 && check_tile(g, pos, 'd'))
 *        pos_swap(g, pos, 'd');
 *    if (dir == 4 && check_tile(g, pos, 'r'))
 *        pos_swap(g, pos, 'r');
 *    display_the_thing(g, mlx_put_image_to_window);
 *}
 */

void	*close_game(t_game *g)
{
	exit_w_msg(1, "Exiting", g);
	return (0);
}

int handle(int keycode, t_game *g)
{
	printf("%d\n", keycode);
	/*
	 *if (keycode == W)
	 *    move(g, 1);
	 *if (keycode == A)
	 *    move(g, 2);
	 *if (keycode == S)
	 *    move(g, 3);
	 *if (keycode == D)
	 *    move(g, 4);
	 *if (keycode == ESC)
	 *    w_handle(g);
	 */
	return (g->map->height);
}

void hook_the_things(t_game *g)
{
	mlx_key_hook(g->mlx_win, handle, g);
	mlx_hook(g->mlx_win, 17, 0L, (void *)close_game, g);
}
