/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:43:47 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/13 18:05:20 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animate.h"
#include <stdlib.h>
#include <stdio.h>
#include "MLX42/MLX42.h"


#define WIDTH 640
#define HEIGHT 360


void error(void);

t_sprite new_sprite(char* file_path, mlx_t* mlx) {
  mlx_image_t* img;
  mlx_texture_t* texture;

  // Load png
  texture = mlx_load_png(file_path);
  if (!texture)
    error();

  // Create image from png texture
  img = mlx_texture_to_image(mlx, texture);
  if (!img)
    error();

  mlx_delete_texture(texture);

  return (t_sprite){img, mlx};
}

void    destroy_sprite(t_sprite* s) {
    if (!s)
        error();
    mlx_delete_image(s->mlx, s->sprite_img);
}

static void add_frame(t_animation* a, t_sprite* s, sprite_slice slice, int mirrored) {
    mlx_image_t* frame;

    frame = mlx_new_image(s->mlx, slice.width - (slice.padding_x * 2), slice.height - (slice.padding_y * 2));
    if (!frame)
        error();
    for (int i = 0; i < slice.height - (slice.padding_y * 2); i++) {
        for (int j = 0; j < slice.width - (slice.padding_x * 2); j++) {
            if (mirrored)
                mlx_put_pixel(frame, (slice.height - (slice.padding_y * 2)) - j - 1, i, mlx_get_pixel(s->sprite_img, slice.x + j + slice.padding_x, slice.y + i + slice.padding_y));
            else
                mlx_put_pixel(frame, j, i, mlx_get_pixel(s->sprite_img, slice.x + j + slice.padding_x, slice.y + i + slice.padding_y));
        }
    }
    ft_lstadd_back(&a->frames, ft_lstnew(frame));
}

t_animation* slice_sprite(t_sprite* s, sprite_slice slice, int mirrored, int frames, int delay) {
    t_animation *   a;

    a = (t_animation*)calloc(sizeof(t_animation), 1);
    if (!a)
        error();
    *a = (t_animation){NULL, delay, 0, 0, mirrored, 0, 0};
    for (int i = 0; i < frames; i++) {
        add_frame(a, s, slice, mirrored);
        slice.x += slice.width;
        if ((uint32_t)slice.x >= s->sprite_img->width) {
            slice.x = 0;
            slice.y += slice.height;
        }
    }
    return (a);
}


typedef struct s_color_game {
  mlx_t * mlx;
  mlx_image_t * menu_bg;
  t_animation * select_animation;
} t_color_game;

void error(void) {
  puts(mlx_strerror(mlx_errno));
  exit(EXIT_FAILURE);
}

void bait(void*ptr){(void)ptr;};

t_color_game init_game() {
  mlx_t*          mlx;
  mlx_image_t*    img;
  t_animation*    anim;
  t_sprite        sprite;

  // Initialize mlx
  mlx = mlx_init(WIDTH, HEIGHT, "Color Game", false);
  if (!mlx)
    error();

  // Initialize sprite from the image file to be used as the background
  sprite = new_sprite("./images/spritesheet(1).png", mlx);

  // Convert sprite texture to a displayable image for the background
  img = mlx_texture_to_image(mlx, sprite.texture);
  if (!img)
    error();

  // Set up sprite animation if needed
  anim = slice_sprite(&sprite, (sprite_slice){0, 0, 128, 32, 0, 0}, false, 5, 120);

  // Clean up unused resources
  destroy_sprite(&sprite);

  return (t_color_game){mlx, img, anim};
}



int32_t main(void)
{
  t_color_game cg;

  cg = init_game();

  if (mlx_image_to_window(cg.mlx, cg.menu_bg, 0, 0) == -1)
    error();

  mlx_loop(cg.mlx);

  ft_lstclear(&cg.select_animation->frames, bait);
  free(cg.select_animation);
  mlx_terminate(cg.mlx);
  return (EXIT_SUCCESS);
}