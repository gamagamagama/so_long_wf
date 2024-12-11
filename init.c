/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:22:39 by mgavorni          #+#    #+#             */
/*   Updated: 2024/12/11 04:01:10 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lost_in_void.h"

mlx_image_t *init_image(mlx_t *mlx)
{
    mlx_image_t *image;

    image = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    return (image);
}
vp_t *init_viewport()
{
     vp_t *vp;

    vp = malloc(sizeof(vp_t));
    init_vp_var(vp);
    return (vp);
}
complex_data_t *init_complex_data()
{
    complex_data_t *complex;

    complex = malloc(sizeof(complex_data_t));
    init_complex_var(complex);
    return (complex);
}
graph_data_t *init_graph_data()
{
    graph_data_t *graph;

    graph = malloc(sizeof(graph_data_t));
    init_graph_var(graph);
    return (graph);
}
node_t *init_node()
{
    node_t *node;

    node = malloc(sizeof(node_t));
    init_node_var(node);
    return (node);
}
setup_t *init_setup(mlx_t *mlx, mlx_image_t *image)
{
    setup_t *setup;

    setup = malloc(sizeof(setup_t));
    setup->data = init_viewport();
    setup->complex = init_complex_data();
    setup->graph = init_graph_data();
    setup->node = init_node();
    setup->mlx = mlx;
    setup->image = image;
    return (setup);
}
cord_t *init_cord(cord_t **cord)
{
    cord_t *new_cord;
    if (!(cord))
        return NULL;

    new_cord = malloc(sizeof(cord_t));
    if (!new_cord) {
        perror("Failed to allocate memory for cord");
        return NULL;
    }

    new_cord->next = *cord;
    *cord = new_cord;
   new_cord->cord_x = -1;
   new_cord->cord_y = -1;

    return new_cord;
}
game_t *init_game(mlx_t *mlx)
{
    game_t *game;
    setup_t *setup;
    cord_t *cord;

    // Initialize setup, cord, and other dependencies here
    setup = init_setup(mlx, init_image(mlx));
    cord = init_cord(&cord);
    game = malloc(sizeof(game_t));
    game->setup = setup;
    game->cord = cord;
    return (game);
}

assets_t *init_assets(mlx_t *mlx, cord_t *cord, map_t *map)
{
    assets_t *assets;
    game_t *game;

    game = init_game(mlx);
    assets = malloc(sizeof(assets_t));
    assets->game = game;
    assets->game->cord = init_cord(&cord);
    assets->enemy = init_game(mlx);
    assets->enemy->cord = init_cord(&cord);
    assets->player = init_game(mlx);
    assets->player->cord = init_cord(&cord);
    assets->env_back = init_game(mlx);
    assets->env_back->cord = init_cord(&cord);
    assets->env_front = init_game(mlx);
    assets->env_front->cord = init_cord(&cord);
    assets->colect = init_game(mlx);
    assets->colect->cord = NULL;

    assets->game->assets = assets;
    assets->env_back->assets = assets;
    assets->player->assets = assets;
    assets->env_front->assets = assets;
    assets->colect->assets = assets;
    assets->enemy->assets = assets;

    assets->colect->cord = cord;
    assets->player->cord = cord;
    assets->game->cord = cord;
    assets->env_back->cord = cord;
    assets->env_front->cord = cord;
    assets->enemy->cord = cord;

    assets->game->setup->mlx = mlx;
    assets->env_back->setup->mlx = mlx;
    assets->player->setup->mlx = mlx;
    assets->env_front->setup->mlx = mlx;
    assets->colect->setup->mlx = mlx;
    assets->enemy->setup->mlx = mlx;
    
    
     custumizer_pass(assets);
    //  Initialize other dependencies here
    return (assets);
}

map_t *init_map(mlx_t *mlx, game_t *game ,char *path)
{
   map_t *map;
    assets_t *assets;

    assets = init_assets(mlx, game->cord, map);
    map = malloc(sizeof(map_t));
        if (map == NULL)
        {
            perror("Failed to allocate memory for map");
            return NULL;
        }
        
    map->assets = assets;
   
  
    fprintf(stderr, "map init map : %p\n", map);
    map->assets->game->assets = map->assets;
    map->assets->env_back->assets = map->assets;
    map->assets->player->assets = map->assets;
    map->assets->env_front->assets = map->assets;
    map->assets->colect->assets = map->assets;
    map->assets->enemy->assets = map->assets;

    map->assets->colect->cord = NULL;
    map->assets->player->cord = NULL;
    map->assets->enemy->cord = NULL;
    map->assets->env_back->cord = NULL;
    map->assets->env_front->cord = NULL;

    map->assets->game->setup->mlx = mlx;
    map->assets->env_back->setup->mlx = mlx;
    map->assets->player->setup->mlx = mlx;
    map->assets->env_front->setup->mlx = mlx;
    map->assets->colect->setup->mlx = mlx;
    map->assets->enemy->setup->mlx = mlx;

   
    

    
    
    return (map);
}
void init_structures(mlx_t *mlx)
{
   // mlx_t *mlx;
    mlx_image_t *image;
    vp_t *vp;
    complex_data_t *complex;
    graph_data_t *graph;
    node_t *node;
    setup_t *setup;
    cord_t *cord;
    game_t *game;
    assets_t *assets;
    map_t *map;
    
   // mlx = init_mlx_session(WINDOW_WIDTH, WINDOW_HEIGHT, "Lost in Void");
    image = init_image(mlx);
    fprintf(stderr, "image: %p\n", image);
    vp = init_viewport(image);
    fprintf(stderr, "vp: %p\n", vp);
    complex = init_complex_data();
    fprintf(stderr, "complex: %p\n", complex);
    graph = init_graph_data();
    fprintf(stderr, "graph: %p\n", graph);
    node = init_node();
    fprintf(stderr, "node: %p\n", node);
    setup = init_setup(mlx, image);
    fprintf(stderr, "setup: %p\n", setup);
    cord = init_cord(&cord);
    fprintf(stderr, "cord: %p\n", cord);
   
    game = init_game(mlx);
    fprintf(stderr, "game: %p\n", game);

    map = init_map(mlx, game, "map.ber");
    fprintf(stderr, "map: %p\n", map);

    assets = init_assets(mlx, cord, map);
    fprintf(stderr, "assets: %p\n", assets);

    def_map(map);
    map = load_map("map.ber", map);
    map_checks(map);
    map_pathfinder(map);
  
   assets = map->assets;
   
    render(assets);

    // mlx_loop_hook(mlx, time_hook, assets);
   

    mlx_key_hook(mlx, event_handler, assets);

    
    mlx_loop(mlx);
    
    mlx_delete_image(mlx, assets->env_back->setup->image);
    mlx_delete_image(mlx, assets->env_front->setup->image);
    mlx_delete_image(mlx, assets->colect->setup->image);
    mlx_delete_image(mlx, assets->enemy->setup->image);
    mlx_delete_image(mlx, assets->player->setup->image);
    free_game(assets->player);
    free_game(assets->env_back);
    free_game(assets->env_front);
    free_game(assets->colect);
    free_game(assets->enemy);
   
    free_game(assets->game);
    free(assets);
  
}