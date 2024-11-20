/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:55:12 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/12 17:30:04 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    mlx_t *mlx;

    mlx = mlx_init(800, 600, "testing pixel", false);
    if (!mlx)
    {
        fprintf(stderr, "Failed to initialize MLX42\n");
        mlx_terminate(mlx);
        return(EXIT_FAILURE);
    }
    mlx_image_t *img = mlx_new_image(mlx, 800, 600);
    mlx_put_pixel(img, 200, 300, 0xFF0000FF);
    mlx_image_to_window(mlx, img, 0, 100);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return(0);

}

// ➜  game gcc pixel.c -o pixel -I../MLX42/include -L../MLX42/build/ -lmlx42 -lglfw -pthread -lm -ldl
