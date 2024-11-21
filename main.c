/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:39:56 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/08 14:48:23 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../MLX42/include/MLX42/MLX42.h"

#define WIDTH 1280
#define HEIGHT 640

static void error(void)
{
  puts(mlx_strerror(mlx_errno));
  exit(EXIT_FAILURE);
}

int32_t main(void)
{
  // Start mlx
  mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Color Game", false);
  if (!mlx)
        error();

  // Try to load the file
  mlx_texture_t* texture = mlx_load_png("./images/bg_place_holder.png");
  if (!texture)
        error();
  
  // Convert texture to a displayable image
  mlx_image_t* img = mlx_texture_to_image(mlx, texture);
  if (!img)
        error();

  // Display the image
  if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

  mlx_loop(mlx);

  mlx_delete_image(mlx, img);
  mlx_delete_texture(texture);

  // Optional, terminate will clean up any leftover images (not textures!)
  mlx_terminate(mlx);
  return (EXIT_SUCCESS);
}
