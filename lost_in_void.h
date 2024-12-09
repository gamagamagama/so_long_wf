/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lost_in_void.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:29:58 by mgavorni          #+#    #+#             */
/*   Updated: 2024/12/09 03:44:20 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOST_IN_VOID_H
#define LOST_IN_VOID_H

# ifdef M_PI
#undef M_PI
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Int.h"
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
// #include "minilibx-linux/mlx.h"

#define M_PI 3.14159265358979323846
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VIEWPORT_SIZE 50

#define BUFFER_SIZE 1024
// typedef struct tst_node tst_node_t;
// typedef struct complex_data complex_data_t;
// typedef struct graph_data graph_data_t;
// typedef struct vp vp_t;
// typedef struct setup setup_t;


typedef struct assets_s assets_t;
typedef struct cord_s cord_t;

typedef struct tst_node
{
	//mlx_t *mlx;
	int32_t	win_width;
	int32_t	win_height;
	//mlx_image_t *image;
	//int32_t vp_pos_x;
	//int32_t vp_pos_y;
	//int32_t vp_size;
	uint32_t color;
	int	set;

}	node_t;

typedef struct complex_data_s
{
	double	wave_amplitude;
	double	wave_freq;
	double	A; //amplitude in x-direct;
	double	B; // amplitude in y-direct;
	double	a; // freq in x-direct;
	double	b; // freq in y-direct;
	double	delta; //phase difference;
	double	scale_fact;
	double	time;
	double	spiral_fact;
	double	depth;
	double	variable;

} complex_data_t;

typedef struct graph_data_s
{
	int	delta_x; //dx
	int	delta_y; //dy
	int start_x; //x0
	int start_y; //y0
	int end_x; //x1
	int end_y; //y1
	int step_x; //sx
	int	step_y; //sy
	int	error;
	int pixel_x; //px
	int pixel_y; //py
	uint32_t color;
	double thickness;

} graph_data_t;

typedef struct view_port
{
	//tst_node_t *window;
	//complex_data_t *complex_data;
	//graph_data_t *graph_data;
	float vp_position_x;
	float vp_position_y;
	float vp_size_x;
	float vp_size_y;
	int32_t vp_size;

} vp_t;

typedef struct setup_s
{
	vp_t *data;
	complex_data_t *complex;
	graph_data_t *graph;
	node_t	*node;
	mlx_image_t	*image;
	mlx_t	*mlx;
	
}	setup_t;

typedef struct game_s
{
	setup_t *setup;
	assets_t *assets;
	cord_t *cord;
} game_t;

typedef struct assets_s
{
	game_t *game;
	game_t *env_back;
	game_t *env_front;
	game_t *colect;
	game_t *enemy;
	game_t *player;
} assets_t;

typedef struct map_s
{
	assets_t *assets;
	char **grid;
	size_t rows;
	size_t cols;
	int player_count;
	int cord_x;
	int cord_y; 
	int collectible_count;
	int walls;
	int rect;
    int exit_count;
    bool is_valid;

} map_t;

typedef struct cord_s
{
	size_t cord_x;
	size_t cord_y;
	struct cord_s *next;
	
} cord_t;

void debug_env_front(assets_t *assets);
void bresen_line(mlx_image_t *img, graph_data_t *graph_data, vp_t *viewport);
//void key_hook(mlx_key_data_t keydata, void *param);
void update_vp(vp_t *viewport);
void update_data_cp(mlx_image_t *img, int centerX, int centerY, int thickness);
node_t * init_node(void);
void init_vp(vp_t *vp);
void init_all_data(vp_t *data, complex_data_t *complex, graph_data_t *graph, node_t *node);
void init_graph(graph_data_t *graph);
//void init_complex(complex_data_t *complex);
//void draw_square(mlx_image_t *img, uint32_t color);
//void draw_square(mlx_image_t *img, int current_x, int current_y ,vp_t *data);
void draw_square(setup_t *setup, uint32_t color);
void set_up(setup_t *setup);
void print_all(setup_t *setup);
void updateViewport(game_t *asset , int thickness);
void init_graph(graph_data_t *graph);
void customizer(game_t *aset, assets_t *assets);
cord_t *init_cord(cord_t *next);

char	*get_next_line(int fd);
char	*ft_reader(int fd, char *result);
char	*ft_line(char *string_buffer);
char	*ft_next(char *string_buffer);
size_t	ft_strlen(char *result);
char	*ft_strrchr(char *result, int c);
char	*ft_strjoin(char *result, char *string_buffer);
char	*ft_strdup(char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void time_hook( void *param);
void event_handler(mlx_key_data_t keydata, void *param);
void  init_structures(mlx_t *mlx);
void render(assets_t *assets);
void free_game(game_t *game);
void init_complex_var(complex_data_t *complex);
void init_vp_var(vp_t *vp);
void init_node_var(node_t *node);
void init_graph_var(graph_data_t *graph);
void update_viewport(game_t *asset, double thickness);
map_t *init_map(mlx_t *mlx, game_t *game ,char *path);
void custumizer_pass(assets_t *assets);
void def_map(map_t *map);
map_t *load_map(char *path, map_t *map);
void map_checks(map_t *map);

void map_pathfinder(map_t *map);
#endif