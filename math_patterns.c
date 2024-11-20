/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_patterns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:03:24 by mgavorni          #+#    #+#             */
/*   Updated: 2024/11/18 11:24:38 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"  // Include the MLX42 library

#ifdef M_PI
#undef M_PI
#endif

// Redefine M_PI with your preferred value
#define M_PI 3.14159265358979323846



#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VIEWPORT_SIZE 500  // Target size for the pattern in pixels

double waveAmplitude = 10;
double waveFrequency = 3;
int spiralFactor = 1;
int depth = 3;
double A = 100;
double B = 80;
double a = 3;
double b = 2;
double delta = M_PI / 4;
double scalingFactor;  // Scaling factor to control pattern size

// Global images
mlx_image_t *viewport_img = NULL; // On-screen viewport image (50x50 cropped view)

// Viewport position in the window
int viewportPositionX = (WINDOW_WIDTH - VIEWPORT_SIZE) / 2;
int viewportPositionY = (WINDOW_HEIGHT - VIEWPORT_SIZE) / 2;

// Custom function to draw a filled square (to create line thickness)
void draw_filled_square(mlx_image_t *img, int x, int y, int size, uint32_t color) {
    for (int dy = -size; dy <= size; dy++) {
        for (int dx = -size; dx <= size; dx++) {
            int px = x + dx;
            int py = y + dy;
            if (px >= 0 && px < img->width && py >= 0 && py < img->height) {
                mlx_put_pixel(img, px, py, color);
            }
        }
    }
}

// Custom line-drawing function with adjustable thickness
void draw_thick_line(mlx_image_t *img, int x0, int y0, int x1, int y1, int thickness, uint32_t color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        draw_filled_square(img, x0, y0, thickness, color);  // Draw a filled square to simulate thickness
        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

// Function to draw the complex pattern centered on the viewport
void drawComplexPattern(mlx_image_t *img, int centerX, int centerY, int thickness) {
    int prevX = centerX, prevY = centerY;
    mlx_t *mlx = (mlx_t *)thickness;

    for (double t = 0; t < 2 * M_PI * depth; t += 0.05) {
        int x = centerX + (int)(scalingFactor * ((A + t * spiralFactor) * sin(a * t + delta) + waveAmplitude * sin(waveFrequency * t)*tan(waveFrequency)*M_PI));
        int y = centerY + (int)(scalingFactor * ((B + t * spiralFactor) * cos(b * t) + waveAmplitude * cos(waveFrequency * t)* tan(waveFrequency)* M_PI));

        if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
            draw_thick_line(img, prevX, prevY, x, y, thickness, 0xFF0000FF);  // Draw thick line
            if (prevX == prevY)
            {
                x = prevX;
                y = prevY;
                updateViewport(mlx, thickness/2);   
            }
            
        }

        prevX = x;
        prevY = y;
    }
}

// Function to update the viewport by redrawing the complex pattern centered on it
void updateViewport(mlx_t *mlx, int thickness) {
    mlx_delete_image(mlx, viewport_img);
    viewport_img = mlx_new_image(mlx, VIEWPORT_SIZE, VIEWPORT_SIZE);

    // Center of the pattern is set to the center of the viewport
    int patternCenterX = VIEWPORT_SIZE / 2;
    int patternCenterY = VIEWPORT_SIZE / 2;

    // Draw the complex pattern with its center fixed to the viewport center
    drawComplexPattern(viewport_img, patternCenterX, patternCenterY, thickness);

    // Display the viewport at the updated position in the window
    mlx_image_to_window(mlx, viewport_img, viewportPositionX, viewportPositionY);
}

// Key hook to adjust parameters in real-time and move the viewport
void key_hook(mlx_key_data_t keydata, void *param) {
    mlx_t *mlx = (mlx_t *)param;
    static int thickness = 0.1;  // Starting thickness

    if (keydata.key == MLX_KEY_S && keydata.action == MLX_REPEAT) {
        waveAmplitude += 2;  // Increase wave amplitude
        viewportPositionY += 10;  // Move viewport down
        spiralFactor += 1;
    }
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT) {
        waveAmplitude -= 2;  // Decrease wave amplitude
        viewportPositionY -= 10;  // Move viewport up
        spiralFactor -= 1;
    }
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_REPEAT) {
        waveFrequency += 0.2;  // Increase wave frequency
        viewportPositionX += 10;  // Move viewport right
        thickness += 0.1;
    }
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_REPEAT) {
        waveFrequency -= 0.2;  // Decrease wave frequency
        viewportPositionX -= 10;  // Move viewport left
        thickness -= 0.1;
    }
    if (keydata.key == MLX_KEY_T && keydata.action == MLX_REPEAT) {
        spiralFactor += 1;  // Increase spiral factor
    }
    if (keydata.key == MLX_KEY_Y && keydata.action == MLX_REPEAT) {
        spiralFactor -= 1;  // Decrease spiral factor
    }
    if (keydata.key == MLX_KEY_U && keydata.action == MLX_REPEAT) {
        thickness += 1;  // Increase thickness
    }
    if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS && thickness > 0.1) {
        thickness -= 0.1;  // Decrease thickness, but keep it >= 1
    }
    
    // // Update viewport position based on arrow keys
    // if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT) {
    //     viewportOffsetX -= 10;  // Move viewport left
    // }
    // if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT) {
    //     viewportOffsetX += 10;  // Move viewport right
    // }
    // if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_REPEAT) {
    //     viewportOffsetY -= 10;  // Move viewport up
    // }
    // if (keydata.key == MLX_KEY_UP && keydata.action == MLX_REPEAT) {
    //     viewportOffsetY += 10;  // Move viewport down
    // }

    // Ensure viewport stays within the bounds of pattern_img
    viewportPositionX = fmax(0, fmin(viewportPositionX, WINDOW_WIDTH - VIEWPORT_SIZE));
    viewportPositionY = fmax(0, fmin(viewportPositionY, WINDOW_HEIGHT - VIEWPORT_SIZE));

    updateViewport(mlx, thickness);  // Redraw the viewport with updated parameters and offset

}
int main() {
    scalingFactor = 0.1;  // Example scaling factor to fit the pattern in a 50x50 viewport

    mlx_t *mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Pattern Viewport", false);
    if (!mlx) {
        fprintf(stderr, "Failed to initialize MLX42\n");
        return EXIT_FAILURE;
    }

    // Create the on-screen viewport
    viewport_img = mlx_new_image(mlx, VIEWPORT_SIZE, VIEWPORT_SIZE);  // Fixed-size 50x50 viewport

    // Initial draw of the pattern centered within the viewport
    updateViewport(mlx, 1);  // Initial thickness set to 1

    // Set up key hook for interactive adjustments
    mlx_key_hook(mlx, key_hook, mlx);

    // Main loop
    mlx_loop(mlx);

    // Clean up
    mlx_delete_image(mlx, viewport_img);
    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}
