/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MLX42.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:33:15 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/12 17:33:56 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"

#pragma pack(push, 1) // Ensure structures are packed with no padding

typedef struct {
    uint16_t file_type;     // File type, always "BM" for BMP files
    uint32_t file_size;     // Size of the file
    uint16_t reserved1;     // Reserved, always 0
    uint16_t reserved2;     // Reserved, always 0
    uint32_t offset_data;   // Offset to the start of the pixel data
} BMPFileHeader;

typedef struct {
    uint32_t size;              // Size of this header (40 bytes)
    int32_t width;              // Width of the image
    int32_t height;             // Height of the image
    uint16_t planes;            // Number of color planes, must be 1
    uint16_t bit_count;         // Bits per pixel (32 for RGBA)
    uint32_t compression;       // Compression type (0 for no compression)
    uint32_t image_size;        // Image size (can be 0 for uncompressed images)
    int32_t x_pixels_per_meter; // Horizontal resolution (pixels per meter)
    int32_t y_pixels_per_meter; // Vertical resolution (pixels per meter)
    uint32_t colors_used;       // Number of colors in the color palette (0 for default)
    uint32_t colors_important;  // Important colors (0 = all)
} BMPInfoHeader;
