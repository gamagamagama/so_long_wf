/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lost_in_void.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:29:58 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/21 21:39:21 by mgavorni         ###   ########.fr       */
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
	int		spiral_fact;
	int		depth;

} complex_data_t;

typedef struct view_port
{
	tst_node_t *window;
	complex_data_t *complex_data;
	float vp_x;
	float vp_y;
	int32_t vp_size;

} vp_t;



#endif