#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "MLX42/MLX42.h"

typedef struct tst_node {
    mlx_t *mlx;
    int32_t win_width;
    int32_t win_height;
    mlx_image_t *image;
    uint32_t color;
} tst_node_t;

typedef struct view_port {
    tst_node_t *window;
    int32_t vp_x;
    int32_t vp_y;
    int32_t vp_size;
} vp_t;

void draw_square(mlx_image_t *img, vp_t *data)
{
    printf("[DEBUG] Drawing square at (%d, %d) with size %d\n", data->vp_x, data->vp_y, data->vp_size);
    data->window->color = 0x00FF00FF;
    for (int a = 0; a < data->vp_size; a++) {
        for (int b = 0; b < data->vp_size; b++) {
            if ((data->vp_x + a) < img->width && (data->vp_y + b) < img->height) {
                mlx_put_pixel(img, data->vp_x + a, data->vp_y + b, data->window->color);
            }
        }
    }
    printf("[DEBUG] Square drawn successfully\n");
}

void init_viewport(vp_t *viewport, tst_node_t *window)
{
    printf("[DEBUG] Initializing viewport...\n");
    viewport->window = window;
    viewport->vp_size = 50;
    viewport->vp_x = (window->win_width - viewport->vp_size) / 2;
    viewport->vp_y = (window->win_height - viewport->vp_size) / 2;
    printf("[DEBUG] Viewport initialized: vp_x = %d, vp_y = %d, vp_size = %d\n", viewport->vp_x, viewport->vp_y, viewport->vp_size);
}

void update_vp(vp_t *viewport)
{
    printf("[DEBUG] Updating viewport at (%d, %d) with size %d\n", viewport->vp_x, viewport->vp_y, viewport->vp_size);
    tst_node_t *window = viewport->window;

    // Delete old image
    printf("[DEBUG] Deleting old image\n");
    mlx_delete_image(window->mlx, window->image);

    // Create new image
    window->image = mlx_new_image(window->mlx, viewport->vp_size, viewport->vp_size);
    if (!window->image) {
        fprintf(stderr, "[ERROR] Failed to create new image\n");
        return;
    }

    // Draw square and add image to window
    draw_square(window->image, viewport);
    mlx_image_to_window(window->mlx, window->image, viewport->vp_x, viewport->vp_y);
    printf("[DEBUG] Viewport updated successfully\n");
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    vp_t *data = (vp_t *)param;

    printf("[DEBUG] Key press detected: key = %d, action = %d\n", keydata.key, keydata.action);

    if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
        data->vp_y -= 5;
    if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
        data->vp_y += 5;
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
        data->vp_x -= 5;
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
        data->vp_x += 5;

    // Ensure viewport stays within bounds
    data->vp_x = fmax(0, fmin(data->vp_x, data->window->win_width - data->vp_size));
    data->vp_y = fmax(0, fmin(data->vp_y, data->window->win_height - data->vp_size));

    printf("[DEBUG] Updated viewport position: vp_x = %d, vp_y = %d\n", data->vp_x, data->vp_y);

    update_vp(data);
}

int main()
{
    printf("[DEBUG] Starting program...\n");

    vp_t *viewport = malloc(sizeof(vp_t));
    tst_node_t *window = malloc(sizeof(tst_node_t));

    if (!viewport || !window) {
        fprintf(stderr, "[ERROR] Memory allocation failed\n");
        free(viewport);
        free(window);
        return EXIT_FAILURE;
    }

    // Initialize window and viewport
    printf("[DEBUG] Initializing window and viewport\n");
    window->win_width = 800;
    window->win_height = 600;
    window->mlx = mlx_init(window->win_width, window->win_height, "Viewport Example", 0);
    if (!window->mlx) {
        fprintf(stderr, "[ERROR] Failed to initialize MLX\n");
        free(viewport);
        free(window);
        return EXIT_FAILURE;
    }

    init_viewport(viewport, window);

    // Create initial image
    printf("[DEBUG] Creating initial image\n");
    window->image = mlx_new_image(window->mlx, viewport->vp_size, viewport->vp_size);
    if (!window->image) {
        fprintf(stderr, "[ERROR] Failed to create image\n");
        mlx_terminate(window->mlx);
        free(viewport);
        free(window);
        return EXIT_FAILURE;
    }

    draw_square(window->image, viewport);
    mlx_image_to_window(window->mlx, window->image, viewport->vp_x, viewport->vp_y);

    // Set up key hook and event loop
    printf("[DEBUG] Setting up key hook\n");
    mlx_key_hook(window->mlx, key_hook, viewport);

    printf("[DEBUG] Starting MLX event loop\n");
    mlx_loop(window->mlx);

    // Cleanup
    printf("[DEBUG] Cleaning up resources\n");
    mlx_delete_image(window->mlx, window->image);
    mlx_terminate(window->mlx);
    free(viewport);
    free(window);

    printf("[DEBUG] Program exited successfully\n");
    return EXIT_SUCCESS;
}
