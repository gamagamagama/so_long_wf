/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:47:38 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/21 22:17:15 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lost_in_void.h"
void draw_square(mlx_image_t *img, vp_t *data)
{
        printf("[DEBUG] Drawing square at (%f, %f) with size %d\n", data->vp_x, data->vp_y, data->vp_size);

	data->window->color = 0x00FF00FF;
	int row;
	int col;
    int current_x = data->vp_x;
    int current_y = data->vp_y;
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
            if (current_x >= 0 && current_x < data->window->image->width && current_y >= 0 && current_y < data->window->image->height );
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
    printf("[DEBUG] Square drawn\n");

}
void init_complex_data(complex_data_t *compdata)
{
    compdata->delta = M_PI / 4;
    compdata->wave_amplitude = 0;
    compdata->wave_freq = 0;
    compdata->spiral_fact = 0;
    compdata->scale_fact = 0;
    compdata->depth = 0;
    compdata->A = 0;
    compdata->B = 0;
    compdata->a = 0;
    compdata->b = 0;
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

    // vp_t *viewport;
    int centerX;
    int centerY;
    // viewport = viewport;
        printf("[DEBUG] Deleting old image\n");

    mlx_delete_image(viewport->window->mlx, viewport->window->image);
    viewport->window->image = mlx_new_image(viewport->window->mlx, viewport->vp_size, viewport->vp_size);
    // centerX = viewport->vp_size/2;
    // centerY = viewport->vp_size/2;
    draw_square(viewport->window->image, viewport);
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


int main()
{
    vp_t *viewport;
    tst_node_t *window;
    mlx_image_t *viewport_overlay;
    complex_data_t *compdata;

    printf("[DEBUG] Initializing window and viewport\n");
    compdata = malloc(sizeof(complex_data_t));
    viewport = malloc(sizeof(vp_t));
    window = malloc(sizeof(tst_node_t));
    init_window(window);
    init_viewport(viewport);


    //viewport_overlay = viewport->window->image;
    viewport->window->mlx = mlx_init(viewport->window->win_width, viewport->window->win_height, "void", 0);
    if (!(viewport || window))
    {
        free(viewport);
        free(window);
        return(EXIT_FAILURE);
    }
    printf("[DEBUG] Creating initial image\n");
    viewport->window->image = mlx_new_image(window->mlx, viewport->vp_size, viewport->vp_size);
    if (!viewport->window->image)
    {
        printf("[DEBUG] image not created\n");
    }
    
   // viewport->window->image = viewport_overlay;
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