/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-07 16:11:39 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-01-07 16:11:39 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "libft/libft.h"
# include "../mlx so_long/mlx/mlx.h"
# include "GetNextLine/get_next_line.h"


# define UP 13
# define LEFT 0
# define DOWN 1
# define RIGHT 2
# define ESC 53
# define IMG_W 32
# define IMG_H 32
# define WINDOW_NAME "so_long"


typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
	char	**copy;
}	t_map;

typedef struct {
    void	*mlx;
    void	*win;
	char	*filename;
	char	*file;
	char	*line;
    t_map	map;
    void	*player_img_up;
	void	*player_img_right;
	void	*player_img_down;
	void	*player_img_left;
    void	*wall_img;
    void	*collectible_img;
    void	*exit_img;
    void	*background_img;
    int		player_x;
    int		player_y;
    int		moves;
    int		c;
	int		e;
	int		check_c;
	int		check_e;
	int		p;
} t_game;

/*end_game*/
int		close_game(t_game *game);
void	win_game(t_game *game);

/*key_hook.c*/
void	player_pos(t_game *game);
int		update_player(int keycode, t_game *game);

/*map_parse.c*/
void	is_rectangular(t_game *game);
void	check_walls(t_game *game);
int		check_components(t_game *game);
void	check_file(t_game *game);
void	map_parse(t_game *game);

/*movement.c*/
void	move_status(t_game *game, int x, int y, int dir);
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_right(t_game *game);
void	move_left(t_game *game);

/*path_finder.c*/
void	path_traveler(t_game *game, int x, int y);
void	path_finder(t_game *game);

/*read_map*/
void	ft_exit_free(t_game *game);
char	read_map(t_game *game);

/*set_images.c*/
void	set_map_image(t_game *map);
void	set_player_image(t_game *player);
void	render_tile(t_game *game, char tile, int x, int y);
void	render_map(t_game *game);
void	print_moves(t_game *game);

#endif