/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lost_in_void.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:28:45 by mgavorni          #+#    #+#             */
/*   Updated: 2024/12/03 18:54:57 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lost_in_void.h"

void draw_square(setup_t *setup, uint32_t color)
{

	setup->graph->color = color;
	setup->data->vp_x = 0; //position of start drawing square
	setup->data->vp_y = 0; //position  //create new for position and size
	setup->data->vp_size = 100; //owerlay size x and y;
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
				mlx_put_pixel(img, ((int)(setup->data->vp_x) + a), ((int)(setup->data->vp_y) + b), color);
				//fprintf(stderr, "Square is drawing\n");
			}
			b++;
		}
		a++;
	}

	fprintf(stderr, "Square a: %d, b: %d\n", a, b);
	print_all(setup);
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
	fprintf(stderr, "address of complex: %p\n", &complex);
}

void init_node(tst_node_t *node)
{
    mlx_image_t *image;

    image = malloc(sizeof(mlx_image_t));

    node->color = 0x00FF007F;
    //node->image = image;
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

   // data->complex_data = complex;
   // data->graph_data = graph;
    //data->window = node;

    data->vp_size = 20; // size of the overlay in draw_square x and y
    data->vp_size_x = 50; //size of the square x
	data->vp_size_y = 50; //size of the square y
	data->vp_x = 0; // cordinates of the square x
    data->vp_y = 0; 	// coordinates of the square y
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
void draw_thick_line(setup_t *setup, int x0, int y0, int x1, int y1, int thickness, uint32_t color) {
    
	//mlx_image_t *img;
	fprintf(stderr, "ERROR 1: x0: %d, y0: %d, x1: %d, y1: %d, thickness: %d, color: %x\n", x0, y0, x1, y1, thickness, color);

	fprintf(stderr, "Setup error : %p\n", setup);

	
	setup->graph->delta_x = abs(x1 - x0);
    setup->graph->delta_y = abs(y1 - y0);
    setup->graph->step_x = (x0 < x1) ? 1 : -1;
    setup->graph->step_y = (y0 < y1) ? 1 : -1;
    setup->graph->error = setup->graph->delta_x - setup->graph->delta_y;
	fprintf(stderr, "ERROR 2: delta_x: %d, delta_y: %d, step_x: %d, step_y: %d, error: %d\n", setup->graph->delta_x, setup->graph->delta_y, setup->graph->step_x, setup->graph->step_y, setup->graph->error);
    while (1) {
        // draw_square(img, x0, y0, thickness, color);  // Draw a filled square to simulate thickness
       fprintf(stderr, "ERROR 3: x0: %d, y0: %d\n", x0, y0);
	   	draw_square(setup, 0x00FFFF7F);
	    if (x0 == x1 && y0 == y1) break;
        int e2 = setup->graph->error * 2;
        if (e2 > -setup->graph->delta_y) { setup->graph->error -= setup->graph->delta_y; x0 += setup->graph->step_x; }
        if (e2 < setup->graph->delta_x) { setup->graph->error += setup->graph->delta_x; y0 += setup->graph->step_y; }
		fprintf(stderr, "ERROR 4: x0: %d, y0: %d\n", x0, y0);
    }
}
double get_data(setup_t *setup, char *flag)
{
	if(!setup)
	{
		//fprintf(stderr, "setup is null\n");
		return (0);
	}
	if (flag == "wa")
	{
		//fprintf(stderr, "setup->complex->wave_amplitude: %f\n", setup->complex->wave_amplitude);
		return(setup->complex->wave_amplitude);
	}
	else if (flag == "wf")
	{
		//fprintf(stderr, "setup->complex->wave_freq: %f\n", setup->complex->wave_freq);
		return(setup->complex->wave_freq);
	}
	else if (flag == "sp")
	{
		//fprintf(stderr, "setup->complex->spiral_fact: %f\n", setup->complex->spiral_fact);		
		return(setup->complex->spiral_fact);
	}
	else if (flag == "de")
	{	
		//fprintf(stderr, "setup->complex->depth: %f\n", setup->complex->depth);
		return(setup->complex->depth);
	}
	else if (flag == "aa")
	{
		//fprintf(stderr, "setup->complex->A: %f\n", setup->complex->A);
		return(setup->complex->A);
	}
	else if (flag == "bb")
	{
		//fprintf(stderr, "setup->complex->B: %f\n", setup->complex->B);
		return(setup->complex->B);
	}
	else if (flag == "a")
	{
		//fprintf(stderr, "setup->complex->a: %f\n", setup->complex->a);
		return(setup->complex->a);
	}
	else if (flag == "b")
	{
		//fprintf(stderr, "setup->complex->b: %f\n", setup->complex->b);
		return(setup->complex->b);
	}
	else if (flag == "d")
	{
		//fprintf(stderr, "setup->complex->delta: %f\n", setup->complex->delta);
		return(setup->complex->delta);
	}
	else if (flag == "sf")
	{
		//fprintf(stderr, "setup->complex->scale_fact: %f\n", setup->complex->scale_fact);
		return(setup->complex->scale_fact);
	}
	else if (flag == "t")
	{
		//fprintf(stderr, "setup->complex->time: %f\n", setup->complex->time);
		return(setup->complex->time);
	}
	else
	{
		fprintf(stderr, "Wrong flag\n");
		return(0);
	}
	return(0);
}
double get_x(setup_t *setup)
{
	int x;
	double p_x;
	p_x = setup->data->vp_x;
	return( p_x + (int)(get_data(setup, "sf") * (get_data(setup, "aa") 
			+ get_data(setup, "t") * get_data(setup, "sf"))
			 * sin(get_data(setup, "a") * get_data(setup, "t")
			  + get_data(setup, "d") + get_data(setup, "wa")
			  * sin(get_data(setup, "wf") * get_data(setup, "t"))
			   * tan(get_data(setup, "wf"))*M_PI)));
	//fprintf(stderr, "x: %d\n", x);
	//return(x);
}

double get_y(setup_t *setup)
{
	int y;
	double p_y;
	p_y = setup->data->vp_y;
	return( p_y + (int)(get_data(setup, "sf") * (get_data(setup, "bb") 
			+ get_data(setup, "t") * get_data(setup, "sf"))
			 * cos(get_data(setup, "b") * get_data(setup, "t")
			  + get_data(setup, "wa") * cos(get_data(setup, "wf") * get_data(setup, "t"))
			   * tan(get_data(setup, "wf"))* M_PI)));
	//fprintf(stderr, "y: %d\n", y);
	//return(y); 
}
void complex_pattern(setup_t *setup)
{
	double x;
	double y;
	double prev_x;
	double prev_y;
	double t;
	x = setup->data->vp_x;
	y = setup->data->vp_y;
	t = 0;
	prev_x = x;
	prev_y = y;
	double whey = (2 * M_PI * (get_data(setup, "de")));
	fprintf(stderr, "prev_x: %f, prev_y: %f\n whey: %f\n, t: %f", prev_x, prev_y, whey, t);
	while(t < (2 * M_PI * (get_data(setup, "de"))))
	{
		
		x = get_x(setup);
		y = get_y(setup);
		//fprintf(stderr, "x: %d, y: %d\n", x, y);
		if (x >= 0 && x < setup->image->width && y >= 0 && y < setup->image->height)
		{
			fprintf(stderr, "draw_thick_line\n");
			draw_thick_line(setup,(int)prev_x, (int)prev_y, (int)x, (int)y, 1.0f, 0xFFFF007F); //draw_thick_line(setup, 0xFFFF007F);
		}
		prev_x = x;
		prev_y = y;
		t += 0.05;
		//fprintf(stderr, "prev_x: %d, prev_y: %d, t: %f\n", prev_x, prev_y,t);
	}
	setup->complex->time = t;
}
void update_image(setup_t *setup) 
{
	fprintf(stderr, "delete_image\n");
	mlx_delete_image(setup->mlx, setup->image);
	fprintf(stderr, "new_image\n");
	setup->image = mlx_new_image(setup->mlx, setup->data->vp_size_x, setup->data->vp_size_y);
	fprintf(stderr, "complex_pattern\n");
	
	complex_pattern(setup);
	fprintf(stderr, "mlx_image_to_window\n");
	mlx_image_to_window(setup->mlx, setup->image, setup->data->vp_x, setup->data->vp_y);
	
}

void key_hook(mlx_key_data_t keydata, void *param) {
    setup_t *setup = (setup_t *)param;
 //   mlx_t *mlx = (mlx_t *)param;
    setup->graph->thickness = 0.1f;  // Starting thickness
	// float wa = get_data(setup, "wa");
	// int vp_y = setup->data->vp_y;
	// int vp_x = setup->data->vp_x;
	// float wf = get_data(setup, "wf");
	// float sf = get_data(setup, "sf");
	fprintf(stderr, "KEY : %d\n", keydata.key);
	fprintf(stderr, "KEY HOOK\n");	
    if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS) {
		fprintf(stderr, "KEY : S\n");
       setup->complex->wave_amplitude += 2.0f;  // Increase wave amplitude
		setup->data->vp_y += 10.0f;  // Move viewport down
		setup->complex->spiral_fact += 1.0f;
		
		fprintf(stderr, "KEY : Ssetup->complex->spiral_fact: %f\n setup->data->vp_y: %f\n setup->complex->wave_amplitude: %f\n keydata.key: %d\n", setup->complex->spiral_fact, setup->data->vp_y, setup->complex->wave_amplitude,	keydata.key);
    }
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT) {
        setup->complex->wave_amplitude -= 2.0f;  // Decrease wave amplitude
        setup->data->vp_y -= 10.0f;  // Move viewport up
        setup->complex->spiral_fact -= 1.0f;
		fprintf(stderr, "setup->complex->spiral_fact: %f\n setup->data->vp_y: %f\n setup->complex->wave_amplitude: %f\n keydata.key: %d\n", setup->complex->spiral_fact, setup->data->vp_y, setup->complex->wave_amplitude,	keydata.key);
    }
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_REPEAT) {
        setup->complex->wave_freq += 0.2f;  // Increase wave frequency
        setup->data->vp_x += 10.0f;  // Move viewport right
        setup->graph->thickness += 0.1f;
		fprintf(stderr, "setup->data->vp_x: %f\n setup->complex->wave_freq: %f\n thickness: %f\n keydata.key: %d\n", setup->data->vp_x, setup->complex->wave_freq, setup->graph->thickness, keydata.key);
    }
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_REPEAT) {
        setup->complex->wave_freq -= 0.2f;  // Decrease wave frequency
        setup->data->vp_x -= 10.0f;  // Move viewport left
        setup->graph->thickness -= 0.1f;
		fprintf(stderr, "setup->data->vp_x: %f\n setup->complex->wave_freq: %f\n thickness: %f\n keydata.key: %d\n", setup->data->vp_x, setup->complex->wave_freq, setup->graph->thickness, keydata.key);

    }
    if (keydata.key == MLX_KEY_T && keydata.action == MLX_REPEAT) {
        setup->complex->spiral_fact += 1.0f;  // Increase spiral factor
		fprintf(stderr, "setup->complex->spiral_fact: %f\n keydata.key: %d\n", setup->complex->spiral_fact, keydata.key);
    }
    if (keydata.key == MLX_KEY_Y && keydata.action == MLX_REPEAT) {
        setup->complex->spiral_fact -= 1.0f;  // Decrease spiral factor
		fprintf(stderr, "setup->complex->spiral_fact: %f\n keydata.key: %d\n", setup->complex->spiral_fact, keydata.key);
    }
    if (keydata.key == MLX_KEY_U && keydata.action == MLX_REPEAT) {
        setup->graph->thickness += 1.0f;  // Increase thickness
		fprintf(stderr, "thickness: %f\n keydata.key: %d\n", setup->graph->thickness, keydata.key);
    }
    if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS && setup->graph->thickness > 0.1) {
        setup->graph->thickness -= 0.1f;  // Decrease thickness, but keep it >= 1
		fprintf(stderr, "thickness: %f\n keydata.key: %d\n", setup->graph->thickness, keydata.key);
    }
	update_image(setup);
}

void print_all(setup_t *setup)
{
	//setup
	fprintf(stderr, "SETUP\n");
	fprintf(stderr, "setup: %p\n", setup);
	fprintf(stderr, "setup->image: %p\n", setup->image);
	fprintf(stderr, "setup->mlx: %p\n", setup->mlx);
	fprintf(stderr, "setup->node: %p\n", setup->node);
	fprintf(stderr, "setup->graph: %p\n", setup->graph);
	fprintf(stderr, "setup->complex: %p\n", setup->complex);
	fprintf(stderr, "setup->data: %p\n", setup->data);
	fprintf(stderr, "\n");
	//setup->data
	fprintf(stderr, "SETUP->DATA\n");
	fprintf(stderr, "setup->data->vp_x: %f\n", setup->data->vp_x);
	fprintf(stderr, "setup->data->vp_y: %f\n", setup->data->vp_y);
	fprintf(stderr, "setup->data->vp_size_x: %f\n", setup->data->vp_size_x);
	fprintf(stderr, "setup->data->vp_size_y: %f\n", setup->data->vp_size_y);
	fprintf(stderr, "setup->data->vp_size: %d\n", setup->data->vp_size);
	fprintf(stderr, "\n");
	//setup->complex
	fprintf(stderr, "SETUP->COMPLEX\n");
	fprintf(stderr, "setup->complex->wave_amplitude: %f\n", setup->complex->wave_amplitude);
	fprintf(stderr, "setup->complex->wave_freq: %f\n", setup->complex->wave_freq);
	fprintf(stderr, "setup->complex->A: %f\n", setup->complex->A);
	fprintf(stderr, "setup->complex->B: %f\n", setup->complex->B);
	fprintf(stderr, "setup->complex->a: %f\n", setup->complex->a);
	fprintf(stderr, "setup->complex->b: %f\n", setup->complex->b);
	fprintf(stderr, "setup->complex->delta: %f\n", setup->complex->delta);
	fprintf(stderr, "setup->complex->scale: %f\n", setup->complex->scale_fact);
	fprintf(stderr, "setup->complex->time: %f\n", setup->complex->time);
	fprintf(stderr, "setup->complex->spiral_fact: %f\n", setup->complex->spiral_fact);
	fprintf(stderr, "setup->complex->depth: %f\n", setup->complex->depth);
	fprintf(stderr, "\n");
	//setup->graph
	fprintf(stderr, "SETUP->GRAPH\n");
	fprintf(stderr, "setup->graph->delta_y: %d\n", setup->graph->delta_y);
	fprintf(stderr, "setup->graph->delta_x: %d\n", setup->graph->delta_x);
	fprintf(stderr, "setup->graph->start_x: %d\n", setup->graph->start_x);
	fprintf(stderr, "setup->graph->start_y: %d\n", setup->graph->start_y);
	fprintf(stderr, "setup->graph->end_x: %d\n", setup->graph->end_x);
	fprintf(stderr, "setup->graph->end_y: %d\n", setup->graph->end_y);
	fprintf(stderr, "setup->graph->step_x: %d\n", setup->graph->step_x);
	fprintf(stderr, "setup->graph->step_y: %d\n", setup->graph->step_y);
	fprintf(stderr, "setup->graph->error: %d\n", setup->graph->error);
	fprintf(stderr, "setup->graph->color: %x\n", setup->graph->color);
	fprintf(stderr, "setup->graph->thickness: %f\n", setup->graph->thickness);
	fprintf(stderr, "\n");
	//setup->node
	fprintf(stderr, "SETUP->NODE\n");
	fprintf(stderr, "setup->node->win_width: %d\n", setup->node->win_width);
	fprintf(stderr, "setup->node->win_height: %d\n", setup->node->win_height);
	fprintf(stderr, "setup->node->color: %x\n", setup->node->color);
	fprintf(stderr, "setup->node->set: %d\n", setup->node->set);
	fprintf(stderr, "\n");
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
	mlx = mlx_init(setup->node->win_width, setup->node->win_height, "LIV", 0);
	if (!mlx)
	{
		fprintf(stderr,"Failed to initialize MLX\n");
		return(EXIT_FAILURE);
	}
	setup->mlx = mlx;
	fprintf(stderr,"setup.mlx: %p, setup->data->vp_x: %f, setup->data->vp_y: %f\n",setup->mlx, setup->data->vp_x, setup->data->vp_y);
	image = mlx_new_image(setup->mlx, setup->data->vp_size_x, setup->data->vp_size_y);
	if (!image)
	{
		fprintf(stderr,"Failed to create image\n");
		return(EXIT_FAILURE);
	}
	setup->image = image;
	
	complex_pattern(setup);
	fprintf(stderr, "COMPLEX_PATTERN\n");
	mlx_image_to_window(mlx, image, 0, 0);
	fprintf(stderr, "MLX_IMAGE_TO_WINDOW\n");
	mlx_key_hook(mlx, &key_hook, (void*)setup);
	fprintf(stderr, "MLX_KEY_HOOK\n");
	update_image(setup);
	fprintf(stderr, "UPDATE_IMAGE\n");
	print_all(setup);
	//new_square(setup);
	//draw_sqauare(setup->image, setup->data, 0x00FF00FF);
	
	//mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
	
	return(EXIT_SUCCESS);
	//init_all_data(data, complex, graph, node);

}
