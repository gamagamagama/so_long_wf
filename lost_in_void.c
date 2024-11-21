/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lost_in_void.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:28:45 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/20 16:46:05 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lost_in_void.h"

void draw_square(mlx_image_t *img, vp_t *data)
{
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
}
void update_viewport(vp_t *viewport, tst_node_t *window)
{
	mlx_delete_image(window->mlx, window->image);
	window->image = mlx_new_image(window->mlx, viewport->vp_size, viewport->vp_size);
	viewport->vp_x = viewport->vp_size /2;
	viewport->vp_y = viewport->vp_size /2;
	draw_square(window->image, viewport);
	mlx_image_to_window(window->mlx, window->image, viewport->vp_x, viewport->vp_y);
	
}
void key_hook(mlx_key_data_t keydata, void *param)
{
	vp_t *data;

	data = (vp_t *)param;

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
	
	update_viewport(data, data->window);
}

void window_init(tst_node_t *window)
{
	window->win_width = 800;
	window->win_height = 600;
	window->image = NULL;
}
void vp_init(vp_t *viewport, tst_node_t *window)
{

	viewport->window = window;
	viewport->vp_size = 50;
	viewport->vp_x = (viewport->window->win_width - viewport->vp_size) / 2;
	viewport->vp_y = (viewport->window->win_height - viewport->vp_size) / 2;
}

int main() 
{
	//mlx_t *mlx;
	tst_node_t *window;
	vp_t *viewport;

	//mlx_image_t *image;

   // image = window->image;
	viewport = malloc(sizeof(vp_t));
	window = malloc(sizeof(tst_node_t));
	
	window_init(window);
	vp_init(viewport, window);
	window->mlx = mlx_init(window->win_width, window->win_height, "void", 0);
	if (!window->mlx)
	{
		fprintf(stderr,"error mlx init");
		return (EXIT_FAILURE);
	}
	window->image = mlx_new_image(window->mlx, window->win_width, window->win_height);
	if (!window->image)
	{
		fprintf(stderr, "Failed to create image");
		mlx_terminate(window->mlx);
		return (EXIT_FAILURE);
	}
	draw_square(viewport->window->image, viewport);

	if (mlx_image_to_window(window->mlx, window->image, 0, 0) < 0) {
		fprintf(stderr, "Failed to add image to window\n");
		mlx_terminate(window->mlx);
		return EXIT_FAILURE;
	}
	//update_viewport(viewport, window);
	mlx_key_hook(window->mlx, key_hook, viewport);
	mlx_loop(window->mlx); // Start the event loop
	mlx_delete_image(window->mlx, window->image);
	mlx_terminate(window->mlx);
	return EXIT_SUCCESS;

}