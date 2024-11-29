/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lost_in_void.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:28:45 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/29 18:00:16 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lost_in_void.h"

void draw_square(mlx_image_t *img, vp_t *data, uint32_t color)
{
	data->graph_data->color = color;
	// color = 0x00FF00FF;
	int a;
	int b;

	a = 0;
	while (a < data->vp_size) // Iterate for the square size in x-axis
	{
		b = 0; // Reset `b` for each row
		while (b < data->vp_size) // Iterate for the square size in y-axis
		{
			if ((data->vp_x + a) < img->width && (data->vp_y + b) < img->height)
			{
				mlx_put_pixel(img, data->vp_x + a, data->vp_y + b, data->window->color);
			}
			b++;
		}
		a++;
	}
}
void init_graph(graph_data_t *graph)
{
	graph->delta_x = 0;
	graph->delta_y = 0;
	graph->end_x = 0;
	graph->end_y = 0;
	graph->start_x = 0;
	graph->start_y = 0;
	graph->step_x = 0;
	graph->step_y = 0;
	graph->thickness = 0;
	graph->error = 0;
	graph->color = 0x00000000;
}
void init_complex(complex_data_t *complex)
{
	complex->wave_amplitude = 10;
	complex->wave_freq =3;
	complex->spiral_fact = 1;
	complex->depth = 3;
	complex->A = 100;
	complex->B = 80;
	complex->a = 3;
	complex->b = 2;
	complex->delta = M_PI / 4;
	complex->scale_fact = 0.1;
}

void init_node(tst_node_t *node)
{
	mlx_t *mlx;
	mlx_image_t *image;
	mlx = mlx_init(800, 600, "LIV", 0);
	if (!mlx) 
	{
        printf("[DEBUG] MLX initialization failed\n");
		return(EXIT_FAILURE);
	}
	node->color = 0x00000000;
	node->image = &image;
	node->mlx = &mlx;
	node->set = 0;
	node->win_width = 800;
	node->win_height = 600;
}
void init_vp(vp_t *data)
{
	complex_data_t *complex;
	graph_data_t *graph;
	tst_node_t *node;
	if (!data)
	{
		fprintf(stderr, "NO DATA vp_t\n");
		return(EXIT_FAILURE);
	}
	if (!(complex || graph || node))
	{
		fprintf(stderr, "No complex or graph or node set to NULL\n");
		data->complex_data = NULL;
		data->graph_data = NULL;
		data->window = NULL;
	}
	data->vp_size = 50;
	data->complex_data = &complex;
	data->graph_data = &graph;
	data->window = &node;
	data->vp_x = 0;
	data->vp_y = 0;
}

void init_all_data(vp_t *data, complex_data_t *complex, graph_data_t *graph, tst_node_t *node)
{
	init_node(node);
	init_complex(complex);
	init_graph(graph);
	init_vp(data);
}
void init_inside_data(mlx_t *mlx, mlx_image_t *image)
{
	//
}
void set_up(setup_t *setup)
{
	setup->data = malloc(sizeof(vp_t));
	setup->complex = malloc(sizeof(complex_data_t));
	setup->graph = malloc(sizeof(graph_data_t));
	setup->node = malloc(sizeof(tst_node_t));
	init_all_data(setup->data, setup->complex, setup->graph, setup->node);
}
void new_square(setup_t *setup)
{
	draw_square(setup->image, setup->data, 0x00FF00);
}
int main()
{
	setup_t *setup;
	mlx_image_t *image;
	mlx_t *mlx;
	setup = malloc(sizeof(setup_t));
	set_up(setup);

	if (!(setup))
	{
		fprintf(stderr,"Failed malloc of one of the data\n");
		return(EXIT_FAILURE);
	}
	image = mlx_new_image(mlx,setup->data->vp_x,setup->data->vp_y);
	new_square(setup);
	mlx_loop(mlx);
	
	//init_all_data(data, complex, graph, node);

}
