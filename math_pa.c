/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:38:45 by mgavorni          #+#    #+#             */
/*   Updated: 2024/12/04 05:24:09 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lost_in_void.h"



void init_complex_data(complex_data_t *complex) {
    complex->wave_amplitude = 10;
    complex->wave_freq = 3;
    complex->spiral_fact = 1;
    complex->depth = 1;
    complex->A = 100;
    complex->B = 100;
    complex->a = 3;
    complex->b = 2;
    complex->delta = M_PI / 4;
    complex->scale_fact = 0.1;
    complex->time = 0; 
}


void init_vp_data(vp_t *vp) {
    vp->vp_size = VIEWPORT_SIZE;
    vp->vp_position_x = (WINDOW_WIDTH - VIEWPORT_SIZE) / 2;
    vp->vp_position_y = (WINDOW_HEIGHT - VIEWPORT_SIZE) / 2;
    vp->vp_size_x = VIEWPORT_SIZE;
    vp->vp_size_y = VIEWPORT_SIZE;
}

void init_node_data(node_t *node) {
    node->win_width = WINDOW_WIDTH;
    node->win_height = WINDOW_HEIGHT;
    node->color = 0x00000000;
    node->set = 0;
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
    graph->pixel_x = 0;
    graph->pixel_y = 0;
    graph->thickness = 0;
    graph->error = 0;
    graph->color = 0x00000000;

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
    setup->graph = malloc(sizeof(graph_data_t));
    if (!setup->complex || !setup->data || !setup->node || !setup->graph) {
        fprintf(stderr, "Failed to allocate memory for sub-structures\n");
        exit(EXIT_FAILURE);
    }
    init_complex_data(setup->complex);
    init_vp_data(setup->data);
    init_node_data(setup->node);
    init_graph(setup->graph);
    setup->image = NULL;
    return (setup);
}

// Draw a filled square
void draw_filled_square(mlx_image_t *img,graph_data_t *g)
{
   g->delta_y = -g->thickness;
   g->delta_x = -g->thickness;
    while ( g->delta_y <=  g->thickness) 
    {
        g->delta_y++;
        while ( g->delta_x <= g->thickness) 
        {
            g->delta_x++;
            g->pixel_x = g->start_x + g->delta_x;
            g->pixel_y = g->start_y + g->delta_y;
            if (g->pixel_x >= 0 && g->pixel_x < img->width && g->pixel_y >= 0 && g->pixel_y < img->height) 
            {
                mlx_put_pixel(img, g->pixel_x, g->pixel_y, g->color);
            }
        }
    }
}

// Draw a thick line

void draw_thick_line(mlx_image_t *img, graph_data_t *g) 
{
    g->delta_x = abs(g->end_x - g->start_x);
    g->delta_y = abs(g->end_y - g->start_y);
    if (g->start_x < g->end_x)
        g->step_x = 1;
    else
        g->step_x = -1;
    if (g->start_y < g->end_y)
        g->step_y = 1;
    else
        g->step_y = -1;  
    g->error = g->delta_x - g->delta_y;
    while (1) {
        draw_filled_square(img, g);
        if (g->start_x == g->end_x && g->start_y == g->end_y) 
            break;
        int e2 = g->error * 2;
        if (e2 > -g->delta_y) 
        { 
            g->error -= g->delta_y; 
            g->start_x += g->step_x; 
        }
        if (e2 < g->delta_x) 
        { 
            g->error += g->delta_x; 
            g->start_y += g->step_y; 
        }
    }
}

// Draw the pattern
void draw_complex_pattern(setup_t *setup, mlx_image_t *img, graph_data_t *g)
{ 
    complex_data_t *c = setup->complex;
    int center; 
    center = setup->data->vp_size / 2;
    g->start_x = center;
    g->start_y = center;
    g->color = 0x007F7FFF;
    c->time = 0;
    fprintf(stderr, "center: %d\n", center);
    while (c->time < (2 * M_PI * c->depth)) 
    {
        
        g->end_x = center + (int)(c->scale_fact * ((c->A + c->time * c->spiral_fact) * sin(c->a * c->time + c->delta) + c->wave_amplitude * sin(c->wave_freq * c->time))); //* tan(c->wave_freq) * M_PI));
        g->end_y = center + (int)(c->scale_fact * ((c->B + c->time * c->spiral_fact) * cos(c->b * c->time) + c->wave_amplitude * cos(c->wave_freq * c->time)));  //* tan(c->wave_freq) * M_PI));
        if (g->end_x >= 0 && g->end_x < img->width && g->end_y >= 0 && g->end_y < img->height) {
            draw_thick_line(img, g);
        }
        c->time += 0.05;
        g->start_x = g->end_x;
        g->start_y = g->end_y;
    }
}

// Update the viewport
void update_viewport(setup_t *setup, int thickness) {
    graph_data_t *g = setup->graph;
    if (setup->image) mlx_delete_image(setup->mlx, setup->image);
    setup->image = mlx_new_image(setup->mlx, setup->data->vp_size, setup->data->vp_size);
    if (!setup->image) {
        fprintf(stderr, "Failed to create image\n");
        return;
    }
    draw_complex_pattern(setup, setup->image, g);
    mlx_image_to_window(setup->mlx, setup->image, setup->data->vp_position_x, setup->data->vp_position_y);
}

// Handle key events
void key_hook(mlx_key_data_t keydata, void *param) {
    setup_t *setup = (setup_t *)param;
    static int thickness = 1;
    complex_data_t *c = setup->complex;

    if (keydata.key == MLX_KEY_S) {
        c->wave_amplitude += 2;
        setup->data->vp_position_y += 10;
    }
    if (keydata.key == MLX_KEY_W) {
        c->wave_amplitude -= 2;
        setup->data->vp_position_y -= 10;
    }
    if (keydata.key == MLX_KEY_D) {
        c->wave_freq += 0.2;
        setup->data->vp_position_x += 10;
    }
    if (keydata.key == MLX_KEY_A) {
        c->wave_freq -= 0.2;
        setup->data->vp_position_x -= 10;
    }

    update_viewport(setup, thickness);
}

// Main function
int main() {
    setup_t *setup = init_setup();
    setup_t *env = init_setup();
    setup->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Lost in Void", false);
    if (!setup->mlx) {
        fprintf(stderr, "Failed to initialize MLX\n");
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