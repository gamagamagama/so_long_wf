/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:38:45 by mgavorni          #+#    #+#             */
/*   Updated: 2024/12/03 23:33:57 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lost_in_void.h"



void init_complex_data(complex_data_t *complex) {
    complex->wave_amplitude = 10;
    complex->wave_freq = 3;
    complex->spiral_fact = 1;
    complex->depth = 3;
    complex->A = 100;
    complex->B = 80;
    complex->a = 3;
    complex->b = 2;
    complex->delta = M_PI / 4;
    complex->scale_fact = 0.1; 
}


void init_vp_data(vp_t *vp) {
    vp->vp_size = VIEWPORT_SIZE;
    vp->vp_position_x = (WINDOW_WIDTH - VIEWPORT_SIZE) / 2;
    vp->vp_position_y = (WINDOW_HEIGHT - VIEWPORT_SIZE) / 2;
}

void init_node_data(node_t *node) {
    node->win_width = WINDOW_WIDTH;
    node->win_height = WINDOW_HEIGHT;
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
        fprintf(stderr, "Failed to allocate memory for sub-structures\n");
        exit(EXIT_FAILURE);
    }
    init_complex_data(setup->complex);
    init_vp_data(setup->data);
    init_node_data(setup->node);
    setup->image = NULL;
    return setup;
}

// Draw a filled square
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

// Draw a thick line
void draw_thick_line(mlx_image_t *img, int x0, int y0, int x1, int y1, int thickness, uint32_t color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        draw_filled_square(img, x0, y0, thickness, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

// Draw the pattern
void draw_complex_pattern(setup_t *setup, mlx_image_t *img, int centerX, int centerY, int thickness) {
    complex_data_t *c = setup->complex;
    int prevX = centerX, prevY = centerY;

    for (double t = 0; t < 2 * M_PI * c->depth; t += 0.05) {
        int x = centerX + (int)(c->scale_fact * ((c->A + t * c->spiral_fact) * sin(c->a * t + c->delta) + c->wave_amplitude * sin(c->wave_freq * t) * tan(c->wave_freq) * M_PI));
        int y = centerY + (int)(c->scale_fact * ((c->B + t * c->spiral_fact) * cos(c->b * t) + c->wave_amplitude * cos(c->wave_freq * t) * tan(c->wave_freq) * M_PI));

        if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
            draw_thick_line(img, prevX, prevY, x, y, thickness, 0xFF0000FF);
        }
        prevX = x;
        prevY = y;
    }
}

// Update the viewport
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
    setup->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Pattern Viewport", false);
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