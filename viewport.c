/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:47:38 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/29 14:53:11 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lost_in_void.h"

void draw_square(mlx_image_t *img, int current_x, int current_y ,vp_t *data)
{
       // printf("[DEBUG] Drawing square at (%f, %f) with size %d\n", data->vp_x, data->vp_y, data->vp_size);

	//data->window->color = 0x00FF00FF;
	int row;
	int col;
    //current_x = data->vp_x;
    //current_y = data->vp_y;
	row = 0;
	while (row < data->vp_size) // Iterate for the square size in x-axis
	{
       // printf("[DEBUG] size width (%d)\n", a);
		col = 0; // Reset `b` for each row
		while (col < data->vp_size) // Iterate for the square size in y-axis
		{
            current_x = row;
            current_y = col;
          // printf("[DEBUG] data vp_x+a(%f)(%f) < img->width(%d) a\n",data->vp_x, a, img->width);
			//getchar(); //[DEBUG]
            if (current_x >= 0 && current_x < data->window->image->width && current_y >= 0 && current_y < data->window->image->height )
			{

               // printf("[DEBUG] put pixel at x (%f)\n and  y (%f)", data->vp_x+a, data->vp_y + b );
			//	getchar(); //[DEBUG]
                mlx_put_pixel(img, current_x, current_y, data->window->color);
               // printf("[DEBUG] Square is drawing\n");
			}
			col++;
		}
		row++;
        //getchar(); //[DEBUG]
	}
  //  printf("[DEBUG] Square drawn\n");

}
void init_complex_data(complex_data_t *compdata)
{
    compdata->delta = M_PI / 4;
    compdata->wave_amplitude = 10;
    compdata->wave_freq = 3;
    compdata->spiral_fact = 1;
    compdata->scale_fact = 1;
    compdata->depth = 3;
    compdata->A = 100;
    compdata->B = 80;
    compdata->a = 3;
    compdata->b = 2;
}

void init_graph_data(graph_data_t *graph_data)
{
    graph_data->delta_x = 0;
	graph_data->delta_y = 0;
	graph_data->start_x = 0;
	graph_data->start_y = 0;
	graph_data->end_x = 0;
	graph_data->end_y = 0;
	graph_data->step_x = 1;
	graph_data->step_y = 1;
	graph_data->error = 1;
    graph_data->color = 0xFFFFFFFF;
    graph_data->thickness = 1;
}

void init_viewport(vp_t *viewport, tst_node_t *window, complex_data_t *compdata, graph_data_t *graphdata)
{
     printf("[DEBUG] Initializing viewport...\n");

    viewport->window = window;
    viewport->graph_data = graphdata;
    viewport->complex_data = compdata;
    viewport->vp_size = 600;
    viewport->vp_x = (viewport->window->win_width - viewport->vp_size) / 2;
	viewport->vp_y = (viewport->window->win_height - viewport->vp_size) / 2;
    viewport->window->set = 0;
        printf("[DEBUG] Viewport initialized: vp_x = %f, vp_y = %f, vp_size = %d\n", viewport->vp_x, viewport->vp_y, viewport->vp_size);

}
void init_window(tst_node_t *window)
{
        printf("[DEBUG] Initializing window...\n");

	window->win_width = 800;
	window->win_height = 600;
	window->image = NULL;
        printf("[DEBUG] Window initialized: win_width = %d, win_height = %d \n", window->win_height, window->win_width);

}
// void update_data_cp(mlx_image_t *img, int centerX, int centerY, int thickness)
// {
//     vp_t *data;
//     int prevX = centerX;
//     int prevY = centerY;
//     int x;
//     int y = 0;
//     // mlx_t *mlx = (mlx_t *)thickness;
//     data->complex_data->time = 0;
//     while (data->complex_data->time < 2 * M_PI * data->complex_data->depth)
//     {
//         data->complex_data->time += 0.05;
//     }
//     x =  x = centerX + (int)(data->complex_data->scale_fact * ((data->complex_data->A +data->complex_data->time * data->complex_data->spiral_fact) * sin(data->complex_data->a * data->complex_data->time + data->complex_data->delta) + data->complex_data->wave_amplitude * sin(data->complex_data->wave_freq * data->complex_data->time) * tan(data->complex_data->wave_freq)*M_PI));
//     bresen_line(data->graph_data, data);
//     prevX = x;
//     prevY = y;
// }

void drawComplexPattern(mlx_image_t *img, int centerX, int centerY, vp_t *viewport) {
    int prevX = centerX, prevY = centerY;
    int x, y;


    complex_data_t *data;
    graph_data_t *graph_data;
   

    data = viewport->complex_data;
    graph_data = viewport->graph_data;
    graph_data->thickness = 1;

   if (!img ) {
        fprintf(stderr, "Error: Invalid arguments in drawComplexPattern\n");
        return;  // Check for null image and valid thickness
    }
       if (graph_data->thickness <= 0) {
        fprintf(stderr, "Error: Invalid argument thickness\n");
        return;  // Check for null image and valid thickness
    }
   



    for (double t = 0; t < 2 * M_PI * data->depth; t += 0.05) {
        x = centerX + (int)(data->scale_fact * ((data->A + t * data->spiral_fact) * sin(data->a * t + data->delta) + data->wave_amplitude * sin(data->wave_freq * t)*tan(data->wave_freq))*M_PI);
        y = centerY + (int)(data->scale_fact * ((data->B + t * data->spiral_fact) * cos(data->b * t) + data->wave_amplitude * cos(data->wave_freq * t)* tan(data->wave_freq)* M_PI));

        if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
            graph_data->start_x = prevX;
            graph_data->start_y = prevY;
            graph_data->end_x = x;
            graph_data->end_y = y;
            bresen_line(img, graph_data, viewport);  // Draw thick line
        }

        prevX = x;
        prevY = y;
    }
}

void update_vp(vp_t *viewport)
{
        printf("[DEBUG] Updating viewport at (%f, %f) with size %d\n", viewport->vp_x, viewport->vp_y, viewport->vp_size);

    // vp_t *viewport;
    int centerX;
    int centerY;
    // viewport = viewport;
        printf("[DEBUG] Deleting old image\n");

    mlx_delete_image(viewport->window->mlx, viewport->window->image);
    viewport->window->image = mlx_new_image(viewport->window->mlx, viewport->vp_size, viewport->vp_size);
    // centerX = viewport->vp_size/2;
    // centerY = viewport->vp_size/2;
    printf("[DEBUG] change color\n");
    viewport->window->color = 0x00FF00FF;
    //draw_square(viewport->window->image,viewport->vp_x, viewport->vp_y, viewport);
   // bresen_line(viewport->graph_data, viewport);
   // printf("[DEBUG] bresen line works\n");
   //update_data_cp(viewport->window->image, viewport->vp_x, viewport->vp_y, 0.1);
   //  printf("[DEBUG] DrawCP 01 \n");
    drawComplexPattern(viewport->window->image, viewport->graph_data->start_x, viewport->graph_data->start_y, viewport);
    printf("[DEBUG] DrawCP 02\n");
    //getchar();
    mlx_image_to_window(viewport->window->mlx, viewport->window->image, viewport->vp_x, viewport->vp_y);
        printf("[DEBUG] Viewport updated successfully\n");

}

void key_hook(mlx_key_data_t keydata, void *param)
{
    vp_t *data = (vp_t *)param;
    printf("[DEBUG] Key press detected: key = %d, action = %d\n", keydata.key, keydata.action);
    if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == 2))
	{
        if (keydata.action == 2)
        {
            data->vp_y -= 1;
        }
        
		data->vp_y -= 5;
		
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == 2))
	{

        if (keydata.action == 2)
        {
            data->vp_y += 1;
        }
		data->vp_y += 5;
		
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == 2))
	{
         if (keydata.action == 2)
        {
            data->vp_x -= 1;
        }
		data->vp_x -= 5;
		
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == 2))
	{
         if (keydata.action == 2)
        {
            data->vp_x += 1;
        }
		data->vp_x += 5;
	}
	data->vp_x = fmax(0, fmin(data->vp_x, data->window->win_width - data->vp_size));
    data->vp_y = fmax(0, fmin(data->vp_y, data->window->win_height - data->vp_size));
    printf("[DEBUG] Updated viewport position: vp_x = %f, vp_y = %f\n", data->vp_x, data->vp_y);
	update_vp(data);
}

void bresen_line(mlx_image_t *img, graph_data_t *graph_data, vp_t *viewport) {
    int x = graph_data->start_x;
    int y = graph_data->start_y;
    int dx = abs(graph_data->end_x - graph_data->start_x);
    int dy = abs(graph_data->end_y - graph_data->start_y);
    int sx = (graph_data->start_x < graph_data->end_x) ? 1 : -1;
    int sy = (graph_data->start_y < graph_data->end_y) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
            mlx_put_pixel(img, x, y, graph_data->color);
        }
        if (x == graph_data->end_x && y == graph_data->end_y) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x += sx; }
        if (e2 < dx) { err += dx; y += sy; }
    }
}


// void bresen_line(mlx_image_t *img, graph_data_t *graph_data, vp_t *viewport)
// {
//     printf("[DEBUG] Bresen line\n");
//     printf("[DEBUG] bresen data delta %d, %d\n", graph_data->delta_x, graph_data->delta_y);
//     printf("[DEBUG] bresen data start end X %d, %d\n", graph_data->start_x, graph_data->end_x);
//     printf("[DEBUG] bresen data start end Y %d, %d\n", graph_data->start_y, graph_data->end_y);
//     printf("[DEBUG] bresen data step XY %d, %d\n", graph_data->step_x, graph_data->step_y);

//     graph_data->delta_x = abs(graph_data->end_x - graph_data->start_x);
//     graph_data->delta_y = abs(graph_data->end_y - graph_data->start_y);
//     graph_data->step_x = 1;
//     graph_data->step_y = 1;
//     if (graph_data->start_x >= graph_data->end_x)
//     {
//         graph_data->step_x = -1;
//     }
//     if (graph_data->start_y >= graph_data->end_y)
//     {
//         graph_data->step_y = -1;
//     }
//     if (graph_data->delta_x > graph_data->delta_y)
//     {
//         graph_data->error = graph_data->delta_x - graph_data->delta_y;
//     }
//     else
//     {
//         graph_data->error = graph_data->delta_y - graph_data->delta_x;
//     }
//     int prev_x = graph_data->start_x;
//     int prev_y = graph_data->start_y;
//     while (1)
//     {
//         draw_square(img, graph_data->start_x, graph_data->start_y, viewport);
//         if (graph_data->start_x == graph_data->end_x && graph_data->start_y == graph_data->end_y)
//         {
//             break;
//         }
//         if (graph_data->error * 2 >= graph_data->delta_y)
//         {
//             graph_data->error -= graph_data->delta_y;
//             graph_data->start_x += graph_data->step_x;
//         }
//         if (graph_data->error * 2 <= graph_data->delta_x)
//         {
//             graph_data->error += graph_data->delta_x;
//             graph_data->start_y += graph_data->step_y;
//         }
//     }
// }

int main() {
    vp_t *viewport = NULL;
    tst_node_t *window = NULL;
    complex_data_t *compdata = NULL;
    graph_data_t *graph_data = NULL;
  //  mlx_image_t *img = NULL;

    // Allocate memory
    viewport = malloc(sizeof(vp_t));
    window = malloc(sizeof(tst_node_t));
    compdata = malloc(sizeof(complex_data_t));
    graph_data = malloc(sizeof(graph_data_t));

    if (!viewport || !window || !compdata || !graph_data) {
        printf("[DEBUG] Memory allocation failed\n");
        free(viewport);
        free(window);
        free(compdata);
        free(graph_data);
        return EXIT_FAILURE;
    }

   // Initialize structures
    init_window(window);
    init_complex_data(compdata);
    init_graph_data(graph_data);
    init_viewport(viewport, window, compdata, graph_data);
    
    
    printf("[DEBUG] Linking\n");
    viewport->graph_data = graph_data; // Link graph data
    viewport->window = window;        // Link window

    // Initialize MLX window
    window->mlx = mlx_init(window->win_width, window->win_height, "void", 0);
    if (!window->mlx) {
        printf("[DEBUG] MLX initialization failed\n");
        free(viewport);
        free(window);
        free(compdata);
        free(graph_data);
        return EXIT_FAILURE;
    }

    printf("[DEBUG] Creating initial image\n");
    window->image = mlx_new_image(window->mlx, viewport->vp_size, viewport->vp_size);
    if (!window->image) {
        printf("[DEBUG] Failed to create image\n");
    }

   update_vp(viewport); // Update viewport and draw initial content
    
    printf("[DEBUG] Setting up key hook\n");
    mlx_key_hook(window->mlx, key_hook, viewport);

    printf("[DEBUG] Starting MLX event loop\n");
    mlx_loop(window->mlx);

    // Cleanup resources
    printf("[DEBUG] Cleaning up resources\n");
    mlx_delete_image(window->mlx, window->image);
    mlx_terminate(window->mlx);
    free(viewport);
    free(window);
    free(compdata);
    free(graph_data);

    printf("[DEBUG] Program exited successfully\n");
    return EXIT_SUCCESS;
}
