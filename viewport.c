/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:47:38 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/20 18:19:05 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lost_in_void.h"
void draw_square(mlx_image_t *img, vp_t *data)
{
        printf("[DEBUG] Drawing square at (%f, %f) with size %d\n", data->vp_x, data->vp_y, data->vp_size);

	data->window->color = 0x00FF00FF;
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
        printf("[DEBUG] Square drawn successfully\n");

}

void init_viewport(vp_t *viewport)
{
     printf("[DEBUG] Initializing viewport...\n");
    tst_node_t *window;
    viewport->window = window;
    viewport->vp_size = 50;
    viewport->vp_x = (viewport->window->win_width - viewport->vp_size) / 2;
	viewport->vp_y = (viewport->window->win_height - viewport->vp_size) / 2;
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
void update_vp(vp_t *viewport)
{
        printf("[DEBUG] Updating viewport at (%f, %f) with size %d\n", viewport->vp_x, viewport->vp_y, viewport->vp_size);

    vp_t *temp;
    int centerX;
    int centerY;
    temp = viewport;
        printf("[DEBUG] Deleting old image\n");

    mlx_delete_image(temp->window->mlx, temp->window->image);
    temp->window->image = mlx_new_image(viewport->window->mlx, viewport->vp_size, viewport->vp_size);
    // centerX = viewport->vp_size/2;
    // centerY = viewport->vp_size/2;
    draw_square(temp->window->image, temp);
    mlx_image_to_window(temp->window->mlx, temp->window->image, temp->vp_x, temp->vp_y);
        printf("[DEBUG] Viewport updated successfully\n");

}

void key_hook(mlx_key_data_t keydata, void *param)
{
    vp_t *data = (vp_t *)param;
    printf("[DEBUG] Key press detected: key = %d, action = %d\n", keydata.key, keydata.action);
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		data->vp_x += 1;
		
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		data->vp_x -= 1;
		
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		data->vp_y -= 1;
		
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		data->vp_y += 1;
	}
	data->vp_x = fmax(0, fmin(data->vp_x, data->window->win_width - data->vp_size));
    data->vp_y = fmax(0, fmin(data->vp_y, data->window->win_height - data->vp_size));
    printf("[DEBUG] Updated viewport position: vp_x = %f, vp_y = %f\n", data->vp_x, data->vp_y);
	update_vp(data);
}


int main()
{
    vp_t *viewport;
    tst_node_t *window;
    mlx_image_t *viewport_overlay;

    printf("[DEBUG] Initializing window and viewport\n");
    viewport = malloc(sizeof(vp_t));
    window = malloc(sizeof(tst_node_t));
    init_window(window);
    init_viewport(viewport);


    viewport_overlay = viewport->window->image;
    viewport->window->mlx = mlx_init(viewport->window->win_width, viewport->window->win_height, "void", 0);
    if (!(viewport || window))
    {
        free(viewport);
        free(window);
        return(EXIT_FAILURE);
    }
    printf("[DEBUG] Creating initial image\n");
    viewport_overlay = mlx_new_image(window->mlx, viewport->vp_size, viewport->vp_size);
    viewport->window->image = viewport_overlay;
    update_vp(viewport);
    //draw_square(viewport->window->image, viewport);

    
    printf("[DEBUG] Setting up key hook\n");
    mlx_key_hook(window->mlx, key_hook, viewport);

    printf("[DEBUG] Starting MLX event loop\n");
    mlx_loop(window->mlx);
    
    printf("[DEBUG] Cleaning up resources\n");
    mlx_delete_image(window->mlx, viewport_overlay);
    mlx_terminate(window->mlx);
    free(viewport);
    free(window);
    
    printf("[DEBUG] Program exited successfully\n");
    return (EXIT_SUCCESS);

}