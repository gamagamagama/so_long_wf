/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:53:57 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/12 17:37:00 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "MLX42.h"

int main() {
    int width = 50, height = 50;

    // Allocate and fill the buffer with a solid color (example: red)
    uint32_t *buffer = (uint32_t*)malloc(width * height * sizeof(uint32_t));
    if (!buffer) return 1;

    // Set each pixel to a color (red with full opacity as an example)
    uint32_t red_color = 0xFF0000FF; // RGBA format for red
    for (int i = 0; i < width * height; i++) {
        buffer[i] = red_color;
    }

    // Save the sprite as a BMP file
   save_sprite_to_bmp("sprite.bmp", buffer, width, height);

    // Clean up
    free(buffer);

    return 0;
}
