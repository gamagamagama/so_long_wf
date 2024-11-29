/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lost_in_void.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:29:58 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/29 18:00:15 by mgavorni         ###   ########.fr       */
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
#define M_PI 3.14159265358979323846

// typedef struct tst_node tst_node_t;
// typedef struct complex_data complex_data_t;
// typedef struct graph_data graph_data_t;
// typedef struct vp vp_t;
// typedef struct setup setup_t;


typedef struct setup_s
{
	vp_t *data;
	complex_data_t *complex;
	graph_data_t *graph;
	tst_node_t	*node;
	mlx_image_t	*image;
	mlx_t	*mlx;
	
}	setup_t;

typedef struct tst_node
{
	mlx_t *mlx;
	int32_t	win_width;
	int32_t	win_height;
	mlx_image_t *image;
	//int32_t vp_pos_x;
	//int32_t vp_pos_y;
	//int32_t vp_size;
	uint32_t color;
	int	set;

}	tst_node_t;

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
	int		spiral_fact;
	int		depth;

} complex_data_t;

typedef struct graph_data_s
{
	int	delta_x;
	int	delta_y;
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	int step_x;
	int	step_y;
	int	error;
	uint32_t color;
	int thickness;

} graph_data_t;

typedef struct view_port
{
	tst_node_t *window;
	complex_data_t *complex_data;
	graph_data_t *graph_data;
	float vp_x;
	float vp_y;
	int32_t vp_size;

} vp_t;

void bresen_line(mlx_image_t *img, graph_data_t *graph_data, vp_t *viewport);
void key_hook(mlx_key_data_t keydata, void *param);
void update_vp(vp_t *viewport);
void update_data_cp(mlx_image_t *img, int centerX, int centerY, int thickness);
void init_node(tst_node_t *node);
void init_vp(vp_t *vp);
void init_all_data(vp_t *data, complex_data_t *complex, graph_data_t *graph, tst_node_t *node);
void init_graph(graph_data_t *graph);
void init_complex(complex_data_t *complex);
void draw_square(mlx_image_t *img, vp_t *data, uint32_t color);
//void draw_square(mlx_image_t *img, int current_x, int current_y ,vp_t *data);





#endif