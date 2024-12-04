/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:38:45 by mgavorni          #+#    #+#             */
/*   Updated: 2024/12/04 17:35:48 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lost_in_void.h"



void init_complex_data(complex_data_t *complex) {
    complex->wave_amplitude = 10;
    complex->wave_freq = 3;
    complex->spiral_fact = 1;
    complex->depth = 1;
    complex->A = 100;
    complex->B = 100;
    complex->a = 3;
    complex->b = 2;
    complex->delta = M_PI / 4;
    complex->scale_fact = 0.1;
    complex->time = 0; 
}


void init_vp_data(vp_t *vp) {
    vp->vp_size = VIEWPORT_SIZE;
    vp->vp_position_x = (WINDOW_WIDTH - VIEWPORT_SIZE) / 2;
    vp->vp_position_y = (WINDOW_HEIGHT - VIEWPORT_SIZE) / 2;
    vp->vp_size_x = VIEWPORT_SIZE;
    vp->vp_size_y = VIEWPORT_SIZE;
}

void init_node_data(node_t *node) {
    node->win_width = WINDOW_WIDTH;
    node->win_height = WINDOW_HEIGHT;
    node->color = 0x00000000;
    node->set = 0;
}

void init_graph(graph_data_t *graph) 
{
    graph->delta_x = 0;
    graph->delta_y = 0;
    graph->end_x = 0;
    graph->end_y = 0;
    graph->start_x = 0;
    graph->start_y = 0;
    graph->step_x = 0;
    graph->step_y = 0;
    graph->pixel_x = 0;
    graph->pixel_y = 0;
    graph->thickness = 0;
    graph->error = 0;
    graph->color = 0x00000000;

}

game_t *init_game() {
    game_t *game = malloc(sizeof(game_t));
    if (!game) {
        fprintf(stderr, "Failed to allocate memory for setup\n");
        exit(EXIT_FAILURE);
    }
    game->setup = malloc(sizeof(setup_t));
    game->setup->complex = malloc(sizeof(complex_data_t));
    game->setup->data = malloc(sizeof(vp_t));
    game->setup->node = malloc(sizeof(node_t));
    game->setup->graph = malloc(sizeof(graph_data_t));
    if (!game->setup->complex || !game->setup->data || !game->setup->node || !game->setup->graph || !game->setup) {
        fprintf(stderr, "Failed to allocate memory for sub-structures\n");
        exit(EXIT_FAILURE);
    }
    init_complex_data(game->setup->complex);
    init_vp_data(game->setup->data);
    init_node_data(game->setup->node);
    init_graph(game->setup->graph);
    game->setup->image = NULL;
    return (game);
}

// Draw a filled square
void draw_filled_square(mlx_image_t *img,graph_data_t *g)
{
   g->delta_y = -g->thickness;
   g->delta_x = -g->thickness;
    while ( g->delta_y <=  g->thickness) 
    {
        g->delta_y++;
        while ( g->delta_x <= g->thickness) 
        {
            g->delta_x++;
            g->pixel_x = g->start_x + g->delta_x;
            g->pixel_y = g->start_y + g->delta_y;
            if (g->pixel_x >= 0 && g->pixel_x < img->width && g->pixel_y >= 0 && g->pixel_y < img->height) 
            {
                mlx_put_pixel(img, g->pixel_x, g->pixel_y, g->color);
            }
        }
    }
}

// Draw a thick line

void draw_thick_line(mlx_image_t *img, graph_data_t *g) 
{
    g->delta_x = abs(g->end_x - g->start_x);
    g->delta_y = abs(g->end_y - g->start_y);
    if (g->start_x < g->end_x)
        g->step_x = 1;
    else
        g->step_x = -1;
    if (g->start_y < g->end_y)
        g->step_y = 1;
    else
        g->step_y = -1;  
    g->error = g->delta_x - g->delta_y;
    while (1) {
        draw_filled_square(img, g);
        if (g->start_x == g->end_x && g->start_y == g->end_y) 
            break;
        int e2 = g->error * 2;
        if (e2 > -g->delta_y) 
        { 
            g->error -= g->delta_y; 
            g->start_x += g->step_x; 
        }
        if (e2 < g->delta_x) 
        { 
            g->error += g->delta_x; 
            g->start_y += g->step_y; 
        }
    }
}

// Draw the pattern
void draw_complex_pattern(setup_t *setup, mlx_image_t *img, graph_data_t *g)
{ 
    complex_data_t *c = setup->complex;
    int center; 
    center = setup->data->vp_size / 2;
    g->start_x = center;
    g->start_y = center;
    g->color = 0x007F7FFF;
    c->time = 0;
    while (c->time < (2 * M_PI * c->depth)) 
    {
        
        g->end_x = center + (int)(c->scale_fact * ((c->A + c->time * c->spiral_fact) * sin(c->a * c->time + c->delta) + c->wave_amplitude * sin(c->wave_freq * c->time))); //* tan(c->wave_freq) * M_PI));
        g->end_y = center + (int)(c->scale_fact * ((c->B + c->time * c->spiral_fact) * cos(c->b * c->time) + c->wave_amplitude * cos(c->wave_freq * c->time)));  //* tan(c->wave_freq) * M_PI));
        if (g->end_x >= 0 && g->end_x < img->width && g->end_y >= 0 && g->end_y < img->height) {
            draw_thick_line(img, g);
        }
        c->time += 0.05;
        g->start_x = g->end_x;
        g->start_y = g->end_y;
    }
}

// Update the viewport
void update_viewport(setup_t *setup, int thickness) {
    graph_data_t *g = setup->graph;
    if (setup->image) mlx_delete_image(setup->mlx, setup->image);
    setup->image = mlx_new_image(setup->mlx, setup->data->vp_size, setup->data->vp_size);
    if (!setup->image) {
        fprintf(stderr, "Failed to create image\n");
        return;
    }
    draw_complex_pattern(setup, setup->image, g);
    mlx_image_to_window(setup->mlx, setup->image, setup->data->vp_position_x, setup->data->vp_position_y);
}

// Handle key events
void key_hook(mlx_key_data_t keydata, void *param) {
    setup_t *setup = (setup_t *)param;
    static int thickness = 1;
    complex_data_t *c = setup->complex;

    if (keydata.key == MLX_KEY_S) {
        c->wave_amplitude += 2;
        setup->data->vp_position_y += 10;
    }
    if (keydata.key == MLX_KEY_W) {
        c->wave_amplitude -= 2;
        setup->data->vp_position_y -= 10;
    }
    if (keydata.key == MLX_KEY_D) {
        c->wave_freq += 0.2;
        setup->data->vp_position_x += 10;
    }
    if (keydata.key == MLX_KEY_A) {
        c->wave_freq -= 0.2;
        setup->data->vp_position_x -= 10;
    }

    update_viewport(setup, thickness);
}

void free_game(game_t *game) 
{
    free(game->setup->complex);
    free(game->setup->data);
    free(game->setup->node);
    free(game->setup);
    free(game);
}


void mlx_data(game_t *game) 
{
     //env_back->mlx = mlx;
    update_viewport(game->setup, 1);
    //update_viewport(env_back, 1);
    mlx_key_hook(game->setup->mlx, key_hook, game->setup);
  

}
void custumize_game(game_t *game) 
{
    game->setup->complex->wave_amplitude = 10;
    game->setup->complex->wave_freq = 2;
    game->setup->data->vp_position_x = 100;
    game->setup->data->vp_position_y = 100;
    game->setup->graph->color = 0x0000FFFF; // Blue
}
void custumize_env_back(game_t *env_back)
{
    env_back->setup->complex->wave_amplitude = 8;
    env_back->setup->complex->wave_freq = 1.5;
    env_back->setup->data->vp_position_x = 250;
    env_back->setup->data->vp_position_y = 250;
    env_back->setup->graph->color = 0x00FF00FF; // Green
}

void custumize_env_front(game_t *env_front)
{
    env_front->setup->complex->wave_amplitude = 8;
    env_front->setup->complex->wave_freq = 1.5;
    env_front->setup->data->vp_position_x = 0;
    env_front->setup->data->vp_position_y = 0;
    env_front->setup->graph->color = 0x007F00FF; 
}
void custumize_colect(game_t *colect)
{
    colect->setup->complex->wave_amplitude = 8;
    colect->setup->complex->wave_freq = 1.5;
    colect->setup->data->vp_position_x = 0;
    colect->setup->data->vp_position_y = 100;
    colect->setup->graph->color = 0xFF7F00FF; 
}
void custumize_enemy(game_t *enemy)
{
    enemy->setup->complex->wave_amplitude = 8;
    enemy->setup->complex->wave_freq = 1.5;
    enemy->setup->data->vp_position_x = 0;
    enemy->setup->data->vp_position_y = 50;
    enemy->setup->graph->color = 0xFFFFFFFF; 
}
void custumize_player(game_t *player)
{
    player->setup->data->vp_position_x = 300;
    player->setup->data->vp_position_y = 300;
    player->setup->graph->color = 0x00FF7FFF; 
}

void custumizer_pass(assets_t *assets)
{
    customizer(assets->game, assets);
    customizer(assets->env_back, assets);
    customizer(assets->env_front, assets);
    customizer(assets->colect, assets);
    customizer(assets->enemy, assets);
    customizer(assets->player, assets);
}
void customizer(game_t *aset, assets_t *assets)
{
    if (aset == assets->game)
        custumize_game(assets->game);
    else if (aset == assets->env_back)
        custumize_env_back(assets->env_back);
    else if (aset == assets->env_front)
        custumize_env_front(assets->env_front);
    else if (aset == assets->colect)
        custumize_colect(assets->colect);
    else if (aset == assets->enemy)
        custumize_enemy(assets->enemy);
    else if (aset == assets->player)
        custumize_player(assets->player);
}
assets_t *init_assets(mlx_t *mlx) 
{
    assets_t *assets = malloc(sizeof(assets_t));
    
    if(!assets)
    {
        fprintf(stderr, "Failed to allocate memory for assets\n");
        return (NULL);
    }

    assets->game = init_game();
    assets->env_back = init_game();
    assets->env_front = init_game();
    assets->colect = init_game();
    assets->enemy = init_game();
    assets->player = init_game();

    assets->game->setup->mlx = mlx;
    assets->env_back->setup->mlx = mlx;
    assets->env_front->setup->mlx = mlx;
    assets->colect->setup->mlx = mlx;
    assets->enemy->setup->mlx = mlx;
    assets->player->setup->mlx = mlx;

    custumizer_pass(assets);
    
    
    return (assets);
}


// game_t *asset(assets_t *assets, int flag)
// {
//     if (flag == 0)
//         return (assets->player);
//     else if (flag == 1)
//         return (assets->game);
//     else if (flag == 2)
//         return (assets->env_back);
//     else if (flag == 3)
//         return (assets->env_front);
//     else if (flag == 4)
//         return (assets->colect);
//     else if (flag == 5)
//         return (assets->enemy);
//     else
//         return (NULL);
// }

void create_player(game_t *player, mlx_t *mlx)
{
    player->setup->mlx = mlx;
    mlx_data(player);
}

mlx_t *init_mlx_session(int32_t width, int32_t height, char *title)
{
    mlx_t *mlx;
    mlx = mlx_init(width, height, title, false);
    if (!mlx)
    {
        fprintf(stderr, "Failed to initialize MLX\n");
        return NULL;
    }
    return (mlx);
}

void render(assets_t *assets)
{
    update_viewport(assets->game->setup, 1);
    update_viewport(assets->env_back->setup, 1);
    update_viewport(assets->env_front->setup, 1);
    update_viewport(assets->colect->setup, 1);
    update_viewport(assets->enemy->setup, 1);
    
}
// Main function
int main() 
{
    mlx_t *mlx;
    assets_t *assets;

    mlx = init_mlx_session(WINDOW_WIDTH, WINDOW_HEIGHT, "Lost in Void");
    assets = init_assets(mlx);

    render(assets);
    mlx_key_hook(mlx, key_hook, assets->player->setup);

    
    mlx_loop(mlx);

  
    mlx_delete_image(mlx, assets->player->setup->image);
    mlx_delete_image(mlx, assets->env_back->setup->image);
    mlx_delete_image(mlx, assets->env_front->setup->image);
    mlx_delete_image(mlx, assets->colect->setup->image);
    mlx_delete_image(mlx, assets->enemy->setup->image);

    free_game(assets->player);
    free_game(assets->env_back);
    free_game(assets->env_front);
    free_game(assets->colect);
    free_game(assets->enemy);
   
    free_game(assets->game);
    free(assets);
    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}