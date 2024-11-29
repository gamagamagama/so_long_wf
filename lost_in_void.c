/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lost_in_void.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:28:45 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/29 22:29:17 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lost_in_void.h"

void draw_square(setup_t *setup, uint32_t color)
{

	setup->data->graph_data->color = color;
	setup->data->vp_x = 0; //position of start drawing square
	setup->data->vp_y = 0; //position  //create new for position and size
	setup->data->vp_size = 6; //owerlay size x and y;
	mlx_image_t *img = setup->image;
	int a;
	int b;

	a = 0;

	while (a < setup->data->vp_size) // Iterate for the square size in x-axis
	{
		b = 0; // Reset `b` for each row
		while (b < setup->data->vp_size) // Iterate for the square size in y-axis
		{
			if ((setup->data->vp_x + a) < img->width && (setup->data->vp_y + b) < img->height)
			{
				mlx_put_pixel(img, ((int)(setup->data->vp_x) + a), ((int)(setup->data->vp_y) + b), setup->data->graph_data->color);
				//fprintf(stderr, "Square is drawing\n");
			}
			b++;
		}
		a++;
	}

	fprintf(stderr, "Square a: %d, b: %d\n", a, b);
	fprintf(stderr, "square dimensions: %d x %d, color: %x, start_x: %f, start_y: %f\n", setup->data->vp_size, setup->data->vp_size,color, setup->data->vp_x, setup->data->vp_y);
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
	graph->color = 0x00FF007F;
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
    mlx_image_t *image;

    image = malloc(sizeof(mlx_image_t));

    node->color = 0x00FF007F;
    node->image = image;
    node->set = 0;
    node->win_width = 800;
    node->win_height = 600;
}
void init_vp(vp_t *data)
{
    complex_data_t *complex;
    graph_data_t *graph;
    tst_node_t *node;

    complex = malloc(sizeof(complex_data_t));
    graph = malloc(sizeof(graph_data_t));
    node = malloc(sizeof(tst_node_t));

    data->complex_data = complex;
    data->graph_data = graph;
    data->window = node;

    data->vp_size = 0; // size of the overlay in draw_square x and y
    data->vp_x = 100; // size of the square x
    data->vp_y = 100; 	// size of the square y
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
    vp_t *data;
    complex_data_t *complex;
    graph_data_t *graph;
    tst_node_t *node;
    mlx_image_t *image;

    data = malloc(sizeof(vp_t));
    complex = malloc(sizeof(complex_data_t));
    graph = malloc(sizeof(graph_data_t));
    node = malloc(sizeof(tst_node_t));
    image = malloc(sizeof(mlx_image_t));

    setup->data = data;
    setup->complex = complex;
    setup->graph = graph;
    setup->node = node;
    setup->image = image;

    init_all_data(setup->data, setup->complex, setup->graph, setup->node);
}
void new_square(setup_t *setup)
{
	draw_square(setup, 0x00FF007F);
}

void draw_sqauare(mlx_image_t *img, vp_t *data, uint32_t color)
{
	int i = 999;
	int a = 0;
	int b = 0;
	while (i != 0)
	{
		mlx_put_pixel(img, a, b, color);
		a++;
		i--;
		fprintf(stderr, "line is drawing at (%d) i = %d\n",a,i);
	}
	
	
}
int main()
{
	setup_t *setup = {0};

	mlx_image_t *image;
	mlx_t *mlx;
	setup = malloc(sizeof(setup_t));
	
	set_up(setup);
	if (!(setup))
	{
		fprintf(stderr,"Failed malloc of one of the data\n");
		return(EXIT_FAILURE);
	}
	mlx = mlx_init(1000, 1000, "LIV", 0);
	if (!mlx)
	{
		fprintf(stderr,"Failed to initialize MLX\n");
		return(EXIT_FAILURE);
	}
	setup->mlx = mlx;
	fprintf(stderr,"setup.mlx: %p, setup->data->vp_x: %f, setup->data->vp_y: %f\n",setup->mlx, setup->data->vp_x, setup->data->vp_y);
	image = mlx_new_image(setup->mlx, setup->data->vp_x, setup->data->vp_y);
	if (!image)
	{
		fprintf(stderr,"Failed to create image\n");
		return(EXIT_FAILURE);
	}
	setup->image = image;

	new_square(setup);
	//draw_sqauare(setup->image, setup->data, 0x00FF00FF);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
	
	return(EXIT_SUCCESS);
	//init_all_data(data, complex, graph, node);

}
