/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_save_png.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:11:11 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/12 17:36:36 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "MLX42.h"

void save_sprite_to_bmp(const char *filename, uint32_t *buffer, int width, int height) {
    // Open file for writing in binary mode
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    // Define file and info headers
    BMPFileHeader file_header = {0};
    BMPInfoHeader info_header = {0};

    // Fill file header
    file_header.file_type = 0x4D42; // "BM" in hexadecimal
    file_header.file_size = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + (width * height * sizeof(uint32_t));
    file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    // Fill info header
    info_header.size = sizeof(BMPInfoHeader);
    info_header.width = width;
    info_header.height = -height; // Use negative height for top-down bitmap
    info_header.planes = 1;
    info_header.bit_count = 32; // 32 bits per pixel for RGBA
    info_header.compression = 0;
    info_header.image_size = width * height * sizeof(uint32_t);

    // Write headers
    fwrite(&file_header, sizeof(file_header), 1, file);
    fwrite(&info_header, sizeof(info_header), 1, file);

    // Write pixel data (buffer contains the image pixels in RGBA format)
    fwrite(buffer, sizeof(uint32_t), width * height, file);

    // Close file
    fclose(file);

    printf("Sprite saved to %s\n", filename);
}