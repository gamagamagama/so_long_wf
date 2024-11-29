/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuckind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:03:01 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/29 15:30:20 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lost_in_void.h"

void draw_square(uint32_t color, mlx_image_t *img)
{
    printf("[DEBUG] Drawing square...\n");

    int current_x, current_y; // Absolute pixel coordinates being drawn
    int row = 0;             // Iterates over rows of the square
    int col = 0;             // Iterates over columns of the square
    int square_size = 50;    // Size of the square in pixels

    while (row < square_size) {
        col = 0; // Reset column counter for each row
        while (col < square_size) {
            current_x = row; // Current x-coordinate relative to the top-left of the square
            current_y = col; // Current y-coordinate relative to the top-left of the square

            // Ensure pixel is within the bounds of the image
            if (current_x >= 0 && current_x < img->width && current_y >= 0 && current_y < img->height) {
                mlx_put_pixel(img, current_x, current_y, color);
                printf("[DEBUG] Drawing pixel at (%d, %d)\n", current_x, current_y);
            }
            col++; // Move to the next column
        }
        row++; // Move to the next row
    }

    printf("[DEBUG] Finished drawing square.\n");
}
void init_viewport(vp_t *viewport)
{
     printf("[DEBUG] Initializing viewport...\n");
    tst_node_t *window;
    viewport->window = window;
    viewport->vp_size = 50;
    viewport->vp_x = 0;
	viewport->vp_y = 0;
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

int32_t main()
{
    mlx_t *mlx;
    mlx_image_t *img;
    vp_t *data;
    tst_node_t *data2;

    
    data = malloc(sizeof(vp_t));
    data2 = malloc(sizeof(tst_node_t));
    
    init_viewport(data);
    init_window(data2);
printf("[DEBUG] mlx inits");
    mlx = mlx_init(800, 600, "fucking mlx", 0);
    img = mlx_new_image(mlx, 50, 50);
printf("[DEBUG] mlx draw_sq next");
    draw_square(0x00FF00FF, img);
printf("[DEBUG] mlx img_to_win next");
    mlx_image_to_window(mlx,img,0,0);
printf("[DEBUG] mlx loop next");
    mlx_loop(mlx);
}
