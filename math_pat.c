/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:03:24 by mgavorni          #+#    #+#             */
/*   Updated: 2024/12/03 23:33:54 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"  // Include the MLX42 library
#include "lost_in_void.h"

 //mlx_image_t *viewport_img = NULL;

//#define VIEWPORT_SIZE 500  // Target size for the pattern in pixels
double get_data(setup_t *setup, char *flag)
{
	if(!setup)
	{
		//fprintf(stderr, "setup is null\n");
		return (0);
	}
	if (flag == "w") //wa
	{
		//fprintf(stderr, "setup->complex->wave_amplitude: %f\n", setup->complex->wave_amplitude);
		return(setup->complex->wave_amplitude);
	}
	else if (flag == "f") //wf
	{
		//fprintf(stderr, "setup->complex->wave_freq: %f\n", setup->complex->wave_freq);
		return(setup->complex->wave_freq);
	}
	else if (flag == "s") //sp
	{
		//fprintf(stderr, "setup->complex->spiral_fact: %f\n", setup->complex->spiral_fact);		
		return(setup->complex->spiral_fact);
	}
	else if (flag == "d") //de
	{	
		//fprintf(stderr, "setup->complex->depth: %f\n", setup->complex->depth);
		return(setup->complex->depth);
	}
	else if (flag == "a") //aa
	{
		//fprintf(stderr, "setup->complex->A: %f\n", setup->complex->A);
		return(setup->complex->A);
	}
	else if (flag == "b") //bb
	{
		//fprintf(stderr, "setup->complex->B: %f\n", setup->complex->B);
		return(setup->complex->B);
	}
	else if (flag == "c") //a
	{
		//fprintf(stderr, "setup->complex->a: %f\n", setup->complex->a);
		return(setup->complex->a);
	}
	else if (flag == "d") //b
	{
		//fprintf(stderr, "setup->complex->b: %f\n", setup->complex->b);
		return(setup->complex->b);
	}
	else if (flag == "e") //d
	{
		//fprintf(stderr, "setup->complex->delta: %f\n", setup->complex->delta);
		return(setup->complex->delta);
	}
	else if (flag == "g") //sf
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
void data_check(setup_t *setup)
{
    double a = get_data(setup, "a");
    double c = get_data(setup, "c");
    double e = get_data(setup, "e");
    double f = get_data(setup, "f");
    double g = get_data(setup, "g");
    double t = get_data(setup, "t");
    double w = get_data(setup, "w");

    fprintf(stderr, "a: %f, c: %f, e: %f, f: %f, g: %f, t: %f, w: %f\n", a, c, e, f, g, t, w);
}
double get_x(setup_t *setup)
{
	int x;
	double p_x;
	p_x = setup->data->vp_position_x;
	x =  (int)p_x + (int)((get_data(setup, "g") * (get_data(setup, "a") 
			+ get_data(setup, "t") * get_data(setup, "g"))
			 * sin(get_data(setup, "c") * get_data(setup, "t")
			  + get_data(setup, "e") + get_data(setup, "w")
			  * sin(get_data(setup, "f") * get_data(setup, "t"))
			   * tan(get_data(setup, "f"))*M_PI)));
	//fprintf(stderr, "x: %d\n", x);
	return(x);
}

double get_y(setup_t *setup)
{
	int y;
	double p_y;
	p_y = setup->data->vp_position_y;
	y = (int)p_y + (int)((get_data(setup, "g") * (get_data(setup, "b") 
			+ get_data(setup, "t") * get_data(setup, "g"))
			 * cos(get_data(setup, "d") * get_data(setup, "t")
			  + get_data(setup, "w") * cos(get_data(setup, "f") * get_data(setup, "t"))
			   * tan(get_data(setup, "f"))* M_PI)));
	//fprintf(stderr, "y: %d\n", y);
	return(y); 
}
void init_window(node_t *node)
{
    node->win_width = WINDOW_WIDTH;
    node->win_height = WINDOW_HEIGHT;
}

void init_complex( complex_data_t *complex)
{
    complex->wave_amplitude = 10;
    complex->wave_freq = 3;
    complex->spiral_fact = 1;
    complex->depth = 3;
    complex->A = 100;
    complex->B = 80;
    complex->a = 3;
    complex->b = 2;
    complex->delta = M_PI / 4;
    complex->scale_fact = 0.5;  // Scaling factor to control pattern size
}
void init_viewport(vp_t *data)
{
   
    data->vp_position_x = (WINDOW_WIDTH - VIEWPORT_SIZE) / 2;
    data->vp_position_y = (WINDOW_HEIGHT - VIEWPORT_SIZE) / 2;

}

setup_t *init_setup() {
    setup_t *setup = malloc(sizeof(setup_t));
    if (!setup) {
        fprintf(stderr, "Failed to allocate memory for setup\n");
        exit(EXIT_FAILURE);
    }
    setup->complex = malloc(sizeof(complex_data_t));
    setup->data = malloc(sizeof(vp_t));
    setup->node = malloc(sizeof(node_t));
    if (!setup->complex || !setup->data || !setup->node) {
        fprintf(stderr, "Failed to allocate memory for sub-struct\n");
        exit(EXIT_FAILURE);
    }
    init_complex(setup->complex);
    init_viewport(setup->data);
    init_window(setup->node);
    setup->image = NULL;
    return setup;
}

// Global images
 // On-screen viewport image (50x50 cropped view)

// Viewport position in the window

// Custom function to draw a filled square (to create line thickness)
void draw_filled_square(mlx_image_t *img, int x, int y, int size, uint32_t color) {
    for (int dy = -size; dy <= size; dy++) {
        for (int dx = -size; dx <= size; dx++) {
            int px = x + dx;
            int py = y + dy;
            if (px >= 0 && px < img->width && py >= 0 && py < img->height) {
                mlx_put_pixel(img, px, py, color);
            }
        }
    }
}

// Custom line-drawing function with adjustable thickness
void draw_thick_line(mlx_image_t *img, int x0, int y0, int x1, int y1, int thickness, uint32_t color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        draw_filled_square(img, x0, y0, thickness, color);  // Draw a filled square to simulate thickness
        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

// Function to draw the complex pattern centered on the viewport
void draw_complex_pattern(setup_t *setup, mlx_image_t *img, int centerX, int centerY, int thickness) {
   thickness = 1;
    if (!img || thickness <= 0) {
        fprintf(stderr, "Error: Invalid arguments in drawComplexPattern\n");
        return;  // Check for null image and valid thickness
    }

    int prevX = centerX, prevY = centerY;
     data_check(setup);
    for (double t = 0; t < 2 * M_PI * (get_data(setup, "d")); t += 0.05) {
        int x = centerX + (int)get_x(setup); //(int)(scalingFactor * ((A + t * spiralFactor) * sin(a * t + delta) + waveAmplitude * sin(waveFrequency * t)*tan(waveFrequency)*M_PI));
        int y = centerY + (int)get_y(setup);//(int)(scalingFactor * ((B + t * spiralFactor) * cos(b * t) + waveAmplitude * cos(waveFrequency * t)* tan(waveFrequency)* M_PI));
       fprintf(stderr, "y: %d x: %d\n", y, x);
       
        if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
            draw_thick_line(img, prevX, prevY, x, y, thickness, 0xFF0000FF);  // Draw thick line
            // if (prevX == prevY)
            // {
            //     x = prevX;
            //     y = prevY;
            
            // }
        }

        prevX = x;
        prevY = y;
    }
}

// Function to update the viewport by redrawing the complex pattern centered on it
void update_viewport(setup_t *setup, int thickness) {
    if (setup->image) mlx_delete_image(setup->mlx, setup->image);
    setup->image = mlx_new_image(setup->mlx, setup->data->vp_size, setup->data->vp_size);
    if (!setup->image) {
        fprintf(stderr, "Failed to create image\n");
        return;
    }
    int centerX = setup->data->vp_size / 2;
    int centerY = setup->data->vp_size / 2;
    draw_complex_pattern(setup, setup->image, centerX, centerY, thickness);
    mlx_image_to_window(setup->mlx, setup->image, setup->data->vp_position_x, setup->data->vp_position_y);
}

// Key hook to adjust parameters in real-time and move the viewport
void key_hook(mlx_key_data_t keydata, void *param) {
    
    setup_t *setup = (setup_t *)param;
    mlx_t *mlx = setup->mlx;
    static int thickness = 0.1;  // Staprting thickness

    if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS) {
        fprintf(stderr, "KEY : S\n");
        setup->complex->wave_amplitude += 2;  // Increase wave amplitude
        setup->data->vp_position_y += 10;  // Move viewport down
        setup->complex->spiral_fact += 1;
    }
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT) {
        setup->complex->wave_amplitude -= 2;  // Decrease wave amplitude
        setup->data->vp_position_y -= 10;  // Move viewport up
        setup->complex->spiral_fact-= 1;
    }
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_REPEAT) {
       setup->complex->wave_freq += 0.2;  // Increase wave frequency
        setup ->data->vp_position_x += 10;  // Move viewport right
        thickness += 0.1;
    }
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_REPEAT) {
       setup->complex->wave_freq -= 0.2;  // Decrease wave frequency
        setup->data->vp_position_x -= 10;  // Move viewport left
        thickness -= 0.1;
    }
    if (keydata.key == MLX_KEY_T && keydata.action == MLX_REPEAT) {
       setup->complex->spiral_fact += 1;  // Increase spiral factor
    }
    if (keydata.key == MLX_KEY_Y && keydata.action == MLX_REPEAT) {
       setup->complex->spiral_fact -= 1;  // Decrease spiral factor
    }
    if (keydata.key == MLX_KEY_U && keydata.action == MLX_REPEAT) {
        thickness += 1;  // Increase thickness
    }
    if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS && thickness > 0.1) {
        thickness -= 0.1;  // Decrease thickness, but keep it >= 1
    }
    
    // // Update viewport position based on arrow keys
    // if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT) {
    //     viewportOffsetX -= 10;  // Move viewport left
    // }
    // if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT) {
    //     viewportOffsetX += 10;  // Move viewport right
    // }
    // if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_REPEAT) {
    //     viewportOffsetY -= 10;  // Move viewport up
    // }
    // if (keydata.key == MLX_KEY_UP && keydata.action == MLX_REPEAT) {
    //     viewportOffsetY += 10;  // Move viewport down
    // }

    // Ensure viewport stays within the bounds of pattern_img
    setup->data->vp_position_x = fmax(0, fmin(setup->data->vp_position_x, setup->node->win_width - setup->data->vp_size));
    setup->data->vp_position_y = fmax(0, fmin(setup->data->vp_position_y, setup->node->win_height - setup->data->vp_size));

    update_viewport(setup, thickness);  // Redraw the viewport with updated parameters and offset

}
int main() {
    //scalingFactor = 0.1;  // Example scaling factor to fit the pattern in a 50x50 viewport

    setup_t *setup;
    setup = init_setup();

    // vp_t *data;
    // complex_data_t *complex;
    // graph_data_t *graph;
    // tst_node_t *node;
    // mlx_image_t *image;

    // data = malloc(sizeof(vp_t));
    // complex = malloc(sizeof(complex_data_t));
    // graph = malloc(sizeof(graph_data_t));
    // node = malloc(sizeof(tst_node_t));
    // image = malloc(sizeof(mlx_image_t));
    //init_all_data(setup->data, setup->complex, setup->graph, setup->node);
    //init_setup(setup);
   
    
    setup->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Pattern Viewport", false);
    if (!setup->mlx) {
        fprintf(stderr, "Failed to initialize MLX42\n");
        return EXIT_FAILURE;
    }

    update_viewport(setup, 1);
    mlx_key_hook(setup->mlx, key_hook, setup);
    mlx_loop(setup->mlx);

    mlx_delete_image(setup->mlx, setup->image);
    mlx_terminate(setup->mlx);
    free(setup->complex);
    free(setup->data);
    free(setup->node);
    free(setup);
    return EXIT_SUCCESS;
}
