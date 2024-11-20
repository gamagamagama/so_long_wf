#include "../../MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX_COLORS 10000 // Adjust based on expected number of unique colors

typedef struct s_color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} t_color;
// Define bitmap font for hexadecimal digits (0-9, A-F)
const uint8_t font[16][7] = {
    // 0
    {0x1E, 0x33, 0x37, 0x3B, 0x33, 0x1E, 0x00},
    // 1
    {0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},
    // 2
    {0x1E, 0x33, 0x03, 0x0E, 0x18, 0x3F, 0x00},
    // 3
    {0x1E, 0x33, 0x06, 0x03, 0x33, 0x1E, 0x00},
    // 4
    {0x06, 0x0E, 0x1E, 0x36, 0x3F, 0x06, 0x00},
    // 5
    {0x3F, 0x30, 0x3E, 0x03, 0x33, 0x1E, 0x00},
    // 6
    {0x1E, 0x30, 0x3E, 0x33, 0x33, 0x1E, 0x00},
    // 7
    {0x3F, 0x03, 0x06, 0x0C, 0x18, 0x18, 0x00},
    // 8
    {0x1E, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00},
    // 9
    {0x1E, 0x33, 0x33, 0x1F, 0x03, 0x1E, 0x00},
    // A
    {0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00},
    // B
    {0x3E, 0x33, 0x3E, 0x33, 0x33, 0x3E, 0x00},
    // C
    {0x1E, 0x33, 0x30, 0x30, 0x33, 0x1E, 0x00},
    // D
    {0x3C, 0x36, 0x33, 0x33, 0x36, 0x3C, 0x00},
    // E
    {0x3F, 0x30, 0x3E, 0x30, 0x30, 0x3F, 0x00},
    // F
    {0x3F, 0x30, 0x3E, 0x30, 0x30, 0x30, 0x00}
};


void draw_char(mlx_image_t *img, int x, int y, char c, uint32_t color)
{
    if (c >= '0' && c <= '9')
        c -= '0';
    else if (c >= 'A' && c <= 'F')
        c = c - 'A' + 10;
    else
        return; // Unsupported character

    for (int row = 0; row < 7; row++)
    {
        uint8_t row_data = font[(int)c][row];
        for (int col = 0; col < 5; col++)
        {
            if (row_data & (1 << (4 - col)))
            {
                int px = x + col;
                int py = y + row;
                if (px >= 0 && px < img->width && py >= 0 && py < img->height)
                {
                    mlx_put_pixel(img, px, py, color);
                }
            }
        }
    }
}

void draw_text(mlx_image_t *img, int x, int y, const char *text, uint32_t color)
{
    int cursor_x = x;
    for (size_t i = 0; i < strlen(text); i++)
    {
        draw_char(img, cursor_x, y, text[i], color);
        cursor_x += 6; // Advance cursor (5 pixels for character + 1 pixel space)
    }
}
// Font definition, draw_char, and draw_text functions
// (Include the same as in the previous example)

// Function to check if a color already exists
bool color_exists(t_color *colors, size_t color_count, t_color color) {
    for (size_t i = 0; i < color_count; i++) {
        if (colors[i].red == color.red &&
            colors[i].green == color.green &&
            colors[i].blue == color.blue) {
            return true;
        }
    }
    return false;
}

// Function to collect unique colors
size_t collect_unique_colors(mlx_texture_t *texture, t_color *colors) {
    size_t color_count = 0;
    size_t pixel_count = texture->width * texture->height;
    uint8_t *pixels = texture->pixels;

    for (size_t i = 0; i < pixel_count; i++) {
        size_t index = i * 4; // Each pixel has 4 components (RGBA)
        t_color color = {
            .red = pixels[index],
            .green = pixels[index + 1],
            .blue = pixels[index + 2]
        };

        if (!color_exists(colors, color_count, color)) {
            if (color_count >= MAX_COLORS) {
                fprintf(stderr, "Maximum number of unique colors exceeded.\n");
                break;
            }
            colors[color_count++] = color;
        }
    }
    return color_count;
}

// Function to draw the color map
void draw_color_map(mlx_t *mlx, mlx_image_t *img, t_color *colors, size_t color_count) {
    int square_size = 50;
    int squares_per_row = mlx->width / (square_size + 100); // 100 pixels for text
    int x_offset = 10;
    int y_offset = 10;
    int x = x_offset;
    int y = y_offset;

    for (size_t i = 0; i < color_count; i++) {
        uint32_t color_value = (colors[i].red << 24) | (colors[i].green << 16) | (colors[i].blue << 8) | 0xFF;

        // Draw the color square
        for (int dy = 0; dy < square_size; dy++) {
            for (int dx = 0; dx < square_size; dx++) {
                int px = x + dx;
                int py = y + dy;
                if (px >= 0 && px < img->width && py >= 0 && py < img->height) {
                    mlx_put_pixel(img, px, py, color_value);
                }
            }
        }

        // Prepare the color code string
        char color_code[8];
        snprintf(color_code, sizeof(color_code), "%02X%02X%02X", colors[i].red, colors[i].green, colors[i].blue);

        // Draw the color code text
        draw_text(img, x + square_size + 5, y + square_size / 2 - 3, color_code, 0xFFFFFFFF); // White color for text

        // Update positions
        x += square_size + 100; // Move to the next column
        if ((i + 1) % squares_per_row == 0) {
            x = x_offset;
            y += square_size + 20; // Move to the next row
        }
    }
}

// Main function
int main(void)
{
    // Initialize MLX42
    mlx_t *mlx = mlx_init(800, 600, "Unique Color Map", false);
    if (!mlx)
    {
        fprintf(stderr, "Failed to initialize MLX42\n");
        return EXIT_FAILURE;
    }

    // Load the image
    mlx_texture_t *texture = mlx_load_png("images/cat.png");
    if (!texture)
    {
        fprintf(stderr, "Failed to load image\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Collect unique colors
    t_color colors[MAX_COLORS];
    size_t color_count = collect_unique_colors(texture, colors);
    printf("Found %zu unique colors.\n", color_count);

    // Create an image to display the color map
    mlx_image_t *img = mlx_new_image(mlx, mlx->width, mlx->height);
    if (!img)
    {
        fprintf(stderr, "Failed to create image\n");
        mlx_delete_texture(texture);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Display the color map
    draw_color_map(mlx, img, colors, color_count);

    // Display the image in the window
    if (mlx_image_to_window(mlx, img, 0, 0) < 0)
    {
        fprintf(stderr, "Failed to display image\n");
        mlx_delete_image(mlx, img);
        mlx_delete_texture(texture);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Event loop
    mlx_loop(mlx);

    // Cleanup
    mlx_delete_image(mlx, img);
    mlx_delete_texture(texture);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}
