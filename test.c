#include "../../MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_context
{
    mlx_t          *mlx;
    mlx_image_t    *img;
    int32_t         img_x;
    int32_t         img_y;
    int32_t         window_width;
    int32_t         window_height;
}               t_context;

void key_hook(mlx_key_data_t keydata, void *param);

int main(void)
{
    t_context ctx;

    // Initialize window dimensions
    ctx.window_width = 800;
    ctx.window_height = 600;
    ctx.img_x = 0;
    ctx.img_y = 0;

    // Initialize MLX42
    ctx.mlx = mlx_init(ctx.window_width, ctx.window_height, "Moving Image", false);
    if (!ctx.mlx)
    {
        fprintf(stderr, "Failed to initialize MLX42\n");
        return EXIT_FAILURE;
    }

    // Load the texture from the PNG file
    mlx_texture_t *texture = mlx_load_png("images/cat.png");
    if (!texture)
    {
        fprintf(stderr, "Failed to load PNG image\n");
        mlx_terminate(ctx.mlx);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < texture->width * texture->height * 4; i += 4)
{
    uint8_t red   = texture->pixels[i];
    uint8_t green = texture->pixels[i + 1];
    uint8_t blue  = texture->pixels[i + 2];

    // If the pixel is white
    if ((red == 0xFF && green == 0xFF && blue == 0xFF) || ( red == 0xEE && green == 0xEE && blue == 0xEE))
    {
        texture->pixels[i + 3] = 0x00; // Fully transparent
    }
    else
    {
        texture->pixels[i + 3] = 0xFF; // Fully opaque
    }
}

    // Convert the texture to an image
    ctx.img = mlx_texture_to_image(ctx.mlx, texture);
    if (!ctx.img)
    {
        fprintf(stderr, "Failed to convert texture to image\n");
        mlx_delete_texture(texture);
        mlx_terminate(ctx.mlx);
        return EXIT_FAILURE;
    }

    // Clean up the texture as it's no longer needed
    mlx_delete_texture(texture);

    // Display the image at initial position
    if (mlx_image_to_window(ctx.mlx, ctx.img, ctx.img_x, ctx.img_y) < 0)
    {
        fprintf(stderr, "Failed to put image to window\n");
        mlx_delete_image(ctx.mlx, ctx.img);
        mlx_terminate(ctx.mlx);
        return EXIT_FAILURE;
    }

    // Register the key hook
    mlx_key_hook(ctx.mlx, key_hook, &ctx);

    // Start the event loop
    mlx_loop(ctx.mlx);

    // Cleanup
    mlx_delete_image(ctx.mlx, ctx.img);
    mlx_terminate(ctx.mlx);
    return EXIT_SUCCESS;
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_context *ctx = (t_context *)param;

    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        // Move the image based on the key pressed
        if (keydata.key == MLX_KEY_UP)
            ctx->img_y -= 10;
        else if (keydata.key == MLX_KEY_DOWN)
            ctx->img_y += 10;
        else if (keydata.key == MLX_KEY_LEFT)
            ctx->img_x -= 10;
        else if (keydata.key == MLX_KEY_RIGHT)
            ctx->img_x += 10;
        else if (keydata.key == MLX_KEY_ESCAPE)
            mlx_close_window(ctx->mlx); // Close the window on ESC

        // Ensure the image stays within window bounds
        if ((*ctx).img_x < 0)
            (*ctx).img_x = 0;
        else if ((*ctx).img_x > (*ctx).window_width - (*ctx).img->width)
            (*ctx).img_x = (*ctx).window_width - (*ctx).img->width;

        if ((*ctx).img_y < 0)
            (*ctx).img_y = 0;
        else if ((*ctx).img_y > (*ctx).window_height - (*ctx).img->height)
            (*ctx).img_y = (*ctx).window_height - (*ctx).img->height;

        // Update the image position
        mlx_instance_t *instance = &ctx->img->instances[0];
        instance->x = ctx->img_x;
        instance->y = ctx->img_y;
    }
}
