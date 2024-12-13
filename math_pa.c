/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matus <matus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:38:45 by mgavorni          #+#    #+#             */
/*   Updated: 2024/12/09 15:29:56 by matus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lost_in_void.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i]; 
		i++;
	}
	return (dest);
}

char	*ft_strdup(char *s)
{
	unsigned int	i;
	char		*dest;

	i = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!(dest))
	{
		return (NULL);
	}
	return (ft_memcpy(dest, s, i + 1));
}

size_t	ft_strlen(char *result)
{
	size_t	i;

	i = 0;
	if (!result)
		return (0);
	while (result[i] != '\0')
		i++;
	return (i);
}

char	*ft_strrchr(char *result, int c)
{
	int	i;

	i = 0;
	if (!result)
		return (0);
	if (c == '\0')
		return ((char *)&result[ft_strlen(result)]);
	while (result[i])
	{
		if (result[i] == (char)c)
		{
			return ((char *)&result[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *result, char *string_buffer)
{
	size_t	i;
	size_t	j;
	char	*new_s;

	if (!(result))
	{
		result = (char *)malloc(1 * sizeof(char));
		result[0] = '\0';
	}
	if (!result || !string_buffer)
		return (NULL);
	new_s = (char *)malloc(((ft_strlen(result))
				+ (ft_strlen(string_buffer)) + 1) * (sizeof(char)));
	if (!new_s)
		return (NULL);
	i = -1;
	j = 0;
	if (result)
		while (result[++i] != '\0')
			new_s[i] = result[i];
	while (string_buffer[j] != '\0')
		new_s[i++] = string_buffer[j++];
	new_s[ft_strlen(result) + ft_strlen(string_buffer)] = '\0';
	free(result);
	return (new_s);
}
char	*ft_next(char *string_buffer)
{
	char	*next;
	int		i;
	int		j;

	i = 0;
	while (string_buffer[i] && string_buffer[i] != '\n')
		i++;
	if (!string_buffer[i])
	{
		free(string_buffer);
		return (NULL);
	}
	next = malloc((ft_strlen(string_buffer) - i + 1) * sizeof(char));
	i++;
	j = 0;
	while (string_buffer[i])
	{
		next[j++] = string_buffer[i++];
	}
	next[j] = '\0';
	free(string_buffer);
	return (next);
}

char	*ft_line(char *string_buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (string_buffer[i] == '\0')
		return (NULL);
	while (string_buffer[i] && string_buffer[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (line == 0)
		return (NULL);
	i = 0;
	while (string_buffer[i] && string_buffer[i] != '\n')
	{
		line[i] = string_buffer[i];
		i++;
	}
	if (string_buffer[i] == '\n')
	{
		line[i] = string_buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_reader(int fd, char *result)
{
	char	*string_buffer;
	int		byte;

	string_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!string_buffer)
		return (NULL);
	byte = 1;
	while ((!ft_strrchr(result, '\n')) && byte != 0)
	{
		byte = read(fd, string_buffer, BUFFER_SIZE);
		if (byte == -1)
		{
			free(string_buffer);
			return (NULL);
		}
		string_buffer[byte] = '\0';
		result = ft_strjoin(result, string_buffer);
	}
	free(string_buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*string_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	string_buffer = ft_reader(fd, string_buffer);
	if (!string_buffer)
		return (NULL);
	line = ft_line(string_buffer);
	string_buffer = ft_next(string_buffer);
	return (line);
}


void init_complex_var(complex_data_t *complex) {
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
    complex->variable = 1;
}


void init_vp_var(vp_t *vp) {
    vp->vp_size = VIEWPORT_SIZE;
    vp->vp_position_x = (WINDOW_WIDTH - VIEWPORT_SIZE) / 2;
    vp->vp_position_y = (WINDOW_HEIGHT - VIEWPORT_SIZE) / 2;
    vp->vp_size_x = VIEWPORT_SIZE;
    vp->vp_size_y = VIEWPORT_SIZE;
}

void init_node_var(node_t *node) {
    node->win_width = WINDOW_WIDTH;
    node->win_height = WINDOW_HEIGHT;
    node->color = 0x00000000;
    node->set = 0;
}

void init_graph_var(graph_data_t *graph) 
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

// game_t *init_game() {
//     game_t *game = malloc(sizeof(game_t));
//     if (!game) {
//         fprintf(stderr, "Failed to allocate memory for setup\n");
//         exit(EXIT_FAILURE);
//     }
//     game->cord = malloc(sizeof(cord_t));
//     game->setup = malloc(sizeof(setup_t));
//     game->setup->complex = malloc(sizeof(complex_data_t));
//     game->setup->data = malloc(sizeof(vp_t));
//     game->setup->node = malloc(sizeof(node_t));
//     game->setup->graph = malloc(sizeof(graph_data_t));

//     if (!game->setup->complex || !game->setup->data || !game->setup->node || !game->setup->graph || !game->setup) {
//         fprintf(stderr, "Failed to allocate memory for sub-structures\n");
//         exit(EXIT_FAILURE);
//     }
    
//     init_complex_data(game->setup->complex);
//     init_vp_data(game->setup->data);
//     init_node_data(game->setup->node);
//     init_graph(game->setup->graph);
//     game->setup->image = NULL;
//     game->cord->cord_x = 0;
//     game->cord->cord_y = 0;
//     return (game);
// }

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
void recompute_c_variable(complex_data_t *c, assets_t *asset, game_t *ass) 
{
//    fprintf(stderr, "adress of ass in recompute: %p\n", ass);
//    fprintf(stderr, "adress of asset in recompute: %p\n", asset);
//    fprintf(stderr, "adress of ass->assets_colect in recompute: %p\n", ass->assets->colect);
//     fprintf(stderr, "adress of asset->colect in recompute: %p\n", asset->colect);
    int i = 10;
    if (!(ass || c))
    {
        free(c);
        free(ass);
        exit(EXIT_FAILURE);
    }
   // fprintf(stderr, "adress of game_t ass: %p\n adress of assets_t asset->colect: %p\n", ass, asset->colect);
    if (ass == asset->colect)
    {
        c->variable = tan(c->wave_freq) * M_PI;
    }
    else
        c->variable = 1;
        
    
    
}
void draw_complex_pattern(game_t *asset, mlx_image_t *img, graph_data_t *g)
{ 
    assets_t *ass = asset->assets;
    complex_data_t *c = asset->setup->complex;
    int center_x;
    int center_y; 
    center_x = asset->cord->cord_x +  asset->setup->data->vp_size / 2;
    center_y = asset->cord->cord_y + asset->setup->data->vp_size / 2;
    g->start_x = center_x;
    g->start_y = center_y;
    recompute_c_variable(c, ass, asset);
   // fprintf(stderr, "adress of ass: %p\n", ass);
    c->time = 0;
    while (c->time < (2 * M_PI * c->depth)) 
    {
        
        g->end_x = center_x + (int)(c->scale_fact * ((c->A + c->time * c->spiral_fact) * sin(c->a * c->time + c->delta) + c->wave_amplitude * sin(c->wave_freq * c->time)* c->variable)); //* tan(c->wave_freq) * M_PI));
        g->end_y = center_y + (int)(c->scale_fact * ((c->B + c->time * c->spiral_fact) * cos(c->b * c->time) + c->wave_amplitude * cos(c->wave_freq * c->time)* c->variable));  //* tan(c->wave_freq) * M_PI));
        if (g->end_x >= 0 && g->end_x < img->width && g->end_y >= 0 && g->end_y < img->height) {
            draw_thick_line(img, g);
        }
        c->time += 0.05;
        g->start_x = g->end_x;
        g->start_y = g->end_y;
        //recompute_c_variable(c, ass, asset);
       // fprintf(stderr, "c->variable: %f\n", c->variable);
    }
}

void positions_of_assets(game_t *asset)
{
    asset->setup->data->vp_position_x = asset->cord->cord_x - (asset->setup->data->vp_size / 2);
    asset->setup->data->vp_position_y = asset->cord->cord_y - (asset->setup->data->vp_size / 2);
}


// Update the viewport
void update_viewport(game_t *asset, double thickness) {
    graph_data_t *g = asset->setup->graph;
    //assets_t *ass = asset->assets;

    if (asset->setup->image) mlx_delete_image(asset->setup->mlx, asset->setup->image);
    asset->setup->image = mlx_new_image(asset->setup->mlx, asset->setup->data->vp_size, asset->setup->data->vp_size);
    if (!asset->setup->image) {
        fprintf(stderr, "Failed to create image\n");
        return;
    }
//     if (asset == asset->assets->player)
//    {
       
//             positions_of_assets(asset);
//             draw_complex_pattern(asset, asset->setup->image, g);
//            mlx_image_to_window(asset->setup->mlx, asset->setup->image, asset->cord->cord_x, asset->cord->cord_y);

//    }
    
    
  
    draw_complex_pattern(asset, asset->setup->image, g);
    
    mlx_image_to_window(asset->setup->mlx, asset->setup->image, asset->setup->data->vp_position_x, asset->setup->data->vp_position_y);
}
void collectable_animation(game_t *who) 
{
    static double counter = 0;
    if ((counter < 10.0f))
    {   
        counter += 0.1f;
        who->setup->complex->wave_freq += 0.1f;  
    }
    if (counter > 10.0f)
        who->setup->complex->wave_freq -= 0.1f;
    if(who->setup->complex->wave_freq <= 0.0f)
        counter = 0.0f;

}
void wall_animation(game_t *who)
{
    static double counter = 0;
    if ((counter < 10.0f))
    {   
        counter += 0.1f;
        who->setup->complex->wave_freq += 0.1f;  
    }
    if (counter > 10.0f)
        who->setup->complex->wave_freq -= 0.1f;
    if(who->setup->complex->wave_freq <= 0.0f)
        counter = 0.0f;
}
void time_hook( void *param) 
{
    assets_t *asset = (assets_t *)param;
    
    game_t *who;
    //asset = who->assets;
    if (who = asset->colect)
       collectable_animation(who);
       update_viewport(who, who->setup->graph->thickness);
    if (who = asset->env_front)
        wall_animation(who);
        update_viewport(who, who->setup->graph->thickness);
    
    
   // who->setup->complex->wave_amplitude = 1;
    update_viewport(who, who->setup->graph->thickness);
}
// Handle key events
void key_hooker(mlx_key_data_t keydata, void *param) {
    game_t *who = (game_t *)param;
   static int thickness = 1;
    complex_data_t *c = who->setup->complex;
    graph_data_t *g = who->setup->graph;
    assets_t *asset = who->assets;

    if (keydata.key == MLX_KEY_Q) {
        c->wave_amplitude += 10;
        //who->setup->data->vp_position_y += 10;
    }
    if (keydata.key == MLX_KEY_W) {
        c->wave_amplitude -= 10;
       // who->setup->data->vp_position_y -= 10;
    }
    if (keydata.key == MLX_KEY_E) {
        c->wave_freq += 0.1;
        //who->setup->data->vp_position_x += 10;
    }
    if (keydata.key == MLX_KEY_R) {
        c->wave_freq -= 0.1;
        //who->setup->data->vp_position_x -= 10;
    }
    if (keydata.key == MLX_KEY_T)
    {
        c->A += 10;
    }
    if (keydata.key == MLX_KEY_Y)
    {
        c->A -= 10;
    }
    if (keydata.key == MLX_KEY_U)
    {
        c->B += 10;
    }
    if (keydata.key == MLX_KEY_I)
    {
        c->B -= 10;
    }
    if (keydata.key == MLX_KEY_O)
    {
        c->a += 0.1;
    }
    if (keydata.key == MLX_KEY_P)
    {
        c->a -= 0.1;
    }
    if (keydata.key == MLX_KEY_A)
    {
        c->b += 0.1;
    }
    if (keydata.key == MLX_KEY_S)
    {
        c->b -= 0.1;
    }
    if (keydata.key == MLX_KEY_D)
    {
        c->delta += 0.1;
    }
    if (keydata.key == MLX_KEY_F)
    {
        c->delta -= 0.1;
    }
    if (keydata.key == MLX_KEY_G)
    {
        c->scale_fact += 0.01;
    }
    if (keydata.key == MLX_KEY_H)
    {
        c->scale_fact -= 0.01;
    }
    if (keydata.key == MLX_KEY_J)
    {
        c->time += 1.1;
    }
    if (keydata.key == MLX_KEY_K)
    {
        c->time -= 1.1;
    }
    if (keydata.key == MLX_KEY_Z)
    {
        c->spiral_fact += 1.0;
    }
    if (keydata.key == MLX_KEY_X)
    {
        c->spiral_fact -= 1.0;
    }
    if (keydata.key == MLX_KEY_C)
    {
        c->depth += 0.1;
    }
    if (keydata.key == MLX_KEY_V)
    {
        c->depth -= 0.1;
    }
   if (keydata.key == MLX_KEY_LEFT)
   {
       who->setup->data->vp_position_x -= 10;
       fprintf(stderr, "vp_position_x: %f\n", who->setup->data->vp_position_x);
   }
   if (keydata.key == MLX_KEY_RIGHT)
   {
       who->setup->data->vp_position_x += 10;
       fprintf(stderr, "vp_position_x: %f\n", who->setup->data->vp_position_x);
   }
   if (keydata.key == MLX_KEY_UP)
   {
       who->setup->data->vp_position_y -= 10;
       fprintf(stderr, "vp_position_y: %f\n", who->setup->data->vp_position_y);
   }
   if (keydata.key == MLX_KEY_DOWN)
   {
       who->setup->data->vp_position_y += 10;
        fprintf(stderr, "vp_position_y: %f\n", who->setup->data->vp_position_y);

   }
   if (keydata.key == MLX_KEY_N)
   {
     fprintf(stderr, "who : %p\n", who);
    fprintf(stderr," asset->env_front: %p\n, asset->env_back: %p\n ", asset->env_front, asset->env_back);

   }
   
    
    if (keydata.key == MLX_KEY_M)
    {
        fprintf(stderr, "wave_amplitude: %f\n wave_freq: %f\n A: %f\n B: %f\n a: %f\n b: %f\n delta: %f\n scale_fact: %f\n time: %f\n spiral_fact: %f\n depth: %f\n", c->wave_amplitude, c->wave_freq, c->A, c->B, c->a, c->b, c->delta, c->scale_fact, c->time, c->spiral_fact, c->depth);
    }
    
    
  //  fprintf(stderr, "wave_amplitude: %f\n wave_freq: %f\n vp_position_x: %f\n vp_position_y: %f\n", c->wave_amplitude, c->wave_freq, who->setup->data->vp_position_x, who->setup->data->vp_position_y);
    update_viewport(who, thickness);
}
void key_hook(mlx_key_data_t keydata, void *param) {
    game_t *who = (game_t *)param;
    static int thickness = 1;
    complex_data_t *c = who->setup->complex;

    if (keydata.key == MLX_KEY_S) {
        c->wave_amplitude += 2;
        who->setup->data->vp_position_y += 10;
    }
    if (keydata.key == MLX_KEY_W) {
        c->wave_amplitude -= 2;
        who->setup->data->vp_position_y -= 10;
    }
    if (keydata.key == MLX_KEY_D) {
        c->wave_freq += 0.2;
        who->setup->data->vp_position_x += 10;
    }
    if (keydata.key == MLX_KEY_A) {
        c->wave_freq -= 0.2;
        who->setup->data->vp_position_x -= 10;
    }
  //  fprintf(stderr, "wave_amplitude: %f\n wave_freq: %f\n vp_position_x: %f\n vp_position_y: %f\n", c->wave_amplitude, c->wave_freq, who->setup->data->vp_position_x, who->setup->data->vp_position_y);
    update_viewport(who, thickness);
}

void free_game(game_t *game) 
{
    free(game->setup->complex);
    free(game->setup->data);
    free(game->setup->node);
    free(game->setup);
    free(game);
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
    env_back->setup->data->vp_size = 800;
 
   // env_back->setup->complex->scale_fact = 3;
    env_back->setup->data->vp_position_x = 0;
    env_back->setup->data->vp_position_y = 0;
    env_back->setup->graph->color = 0xFF0000FF; // RED
}

void custumize_env_front(game_t *env_front)
{
    env_front->setup->complex->wave_amplitude = 8;
    env_front->setup->complex->wave_freq = 1.5;
    env_front->setup->data->vp_position_x = 0;
    env_front->setup->data->vp_position_y = 0;
    env_front->setup->graph->color = 0xFFFFFFFF; 
}
void custumize_colect(game_t *colect)
{
    colect->setup->complex->wave_amplitude = 8;
    colect->setup->complex->variable =  tan(colect->setup->complex->wave_freq) * M_PI;
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
    player->setup->complex->variable =  1;
    player->setup->data->vp_position_x = WINDOW_WIDTH / 2;
    player->setup->data->vp_position_y = WINDOW_HEIGHT / 2;
    player->setup->graph->color = 0x00FF7FFF; 
}

void custumizer_pass(assets_t *assets)
{
    customizer(assets->game, assets);
    customizer(assets->env_back, assets);
    customizer(assets->player, assets);
    customizer(assets->env_front, assets);
    customizer(assets->colect, assets);
    customizer(assets->enemy, assets);
   
}
void customizer(game_t *aset, assets_t *assets)
{
    if (aset == assets->game)
        custumize_game(assets->game);
    else if (aset == assets->env_back)
        custumize_env_back(assets->env_back);
    else if (aset == assets->player)
        custumize_player(assets->player);
    else if (aset == assets->env_front)
        custumize_env_front(assets->env_front);
    else if (aset == assets->colect)
        custumize_colect(assets->colect);
    else if (aset == assets->enemy)
        custumize_enemy(assets->enemy);
    
    else
        return;
}
// assets_t *init_assets(mlx_t *mlx) 
// {
//     assets_t *assets = malloc(sizeof(assets_t));
//    // fprintf(stderr, "adress of ass in init_assets: %p\n", assets);
//     if(!assets)
//     {
//         fprintf(stderr, "Failed to allocate memory for assets\n");
//         return (NULL);
//     }

//     assets->game = init_game();
//     assets->env_back = init_game();
//     assets->env_front = init_game();
//     assets->colect = init_game();
//     assets->enemy = init_game();
//     assets->player = init_game();
    
    
   
    
//     assets->game->assets = assets;
//     assets->env_back->assets = assets;
//     assets->player->assets = assets;
//     assets->env_front->assets = assets;
//     assets->colect->assets = assets;
//     assets->enemy->assets = assets;

//     assets->game->setup->mlx = mlx;
//     assets->env_back->setup->mlx = mlx;
//     assets->player->setup->mlx = mlx;
//     assets->env_front->setup->mlx = mlx;
//     assets->colect->setup->mlx = mlx;
//     assets->enemy->setup->mlx = mlx;
   

//     custumizer_pass(assets);
    
    
//     return (assets);
// }


// MLX functions
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
    update_viewport(assets->player, 1);
    update_viewport(assets->game, 1);
    update_viewport(assets->env_back, 1);
    update_viewport(assets->env_front, 1);
    update_viewport(assets->colect, 1);
    update_viewport(assets->enemy, 1);
    
}

void event_handler(mlx_key_data_t keydata, void *param)
{
    int test = 0;
    assets_t *assets = (assets_t *)param;
    if (test == 0)
        key_hook(keydata, assets->player);
    if (test == 1)
        key_hooker(keydata, assets->env_back);

    //time_hook(assets->colect);
    
}
void def_map(map_t *map)
{
    map->grid = NULL;
    map->rows = 0;
    map->cols = 0;
    map->player_count = 0;
    map->collectible_count = 0;
    map->exit_count = 0;
    map->walls = 1;
    map->rect = 1;
    map->cord_x = 0;
    map->cord_y = 0;
    map->is_valid = false;
}
map_t *load_map(char *path, map_t *map)
{
    int fd;
    int x = 0;
    int y = 0;
    char *line = NULL;
    def_map(map);
    fd = open(path, O_RDONLY);
    fprintf(stderr, "fd: %d\n", fd);
    map->grid = malloc(sizeof(char *) * (map->cols + 1));
    if (map->grid == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for map grid\n");
        return NULL;
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0])
        {
            if (map->cols == 0)
            {
                map->cols = ft_strlen(line) - 1;
                fprintf(stderr, "cols: %ld\n", map->cols);
                free(map->grid);
                map->grid = malloc(sizeof(char *) * (map->cols + 1));
                if (map->grid == NULL)
                {
                    fprintf(stderr, "Failed to allocate memory for map grid 2\n");
                    return NULL;
                }
                fprintf(stderr, "cols updated:\n");
            }
            map->grid[x] = line;
            fprintf(stderr, "x: %d\n", x);
            x++;
            map->rows++;
            fprintf(stderr, "line: %s\n", line);
            fprintf(stderr, "map->grid: %s\n", map->grid[x - 1]);
            fprintf(stderr, "rows: %ld\n", map->rows);
        }
        else
        {
            free(line);
        }
    }
    fprintf(stderr, "y: %d\n", y);
    map->grid[x] = NULL;
    close(fd);
    fprintf(stderr, "map load map : %p\n", map);
    return (map);
}
void check_walls(map_t *map)
{
    size_t i = 0;
    size_t j = 0;
    
    fprintf(stderr, "check_walls\n");
   
    j = 0;

    while (j < map->cols)
    {
        if (map->grid[0][j] != '1' || map->grid[map->rows - 1][j] != '1')
        {
            fprintf(stderr, "map->grid[0][j]: %c\n", map->grid[0][j]);
            map->walls = 0;
            fprintf(stderr, "map not valid at position: i: %ld j: %ld , (ASCII :%d\n",i, j, map->grid[i][j]);
        }
        
        j++;
    }
    i = 0;
    while (i < map->rows)
    {
        if (ft_strlen(map->grid[i]) - 1 != map->cols)
        {
            map->rect = 0;
            fprintf(stderr, "1_map len of map->grid[i]: %ld\n", ft_strlen(map->grid[i]));
            fprintf(stderr, "1_map cols : %ld\n", map->cols);
            fprintf(stderr, "1_map not valid at position: i: %ld j: %ld , (ASCII :%d\n",i, j, map->grid[i][j]);
        }
        if (map->grid[i][0] != '1' || map->grid[i][map->cols - 1] != '1')
        {
            fprintf(stderr, "map->grid[i][0]: %c\n", map->grid[i][0]);
            map->walls = 0;
            fprintf(stderr, "map not valid at position: i: %ld j: %ld , (ASCII :%d\n",i, j, map->grid[i][j]);
        }
        i++;
    }
    fprintf(stderr, "map->grid[7][19]: %c\n", map->grid[7][19]);
    
}
void map_checks(map_t *map)
{
    fprintf(stderr, "map address: %p\n", map);
    size_t i = 0;
    size_t j = 0;
    while (i < map->rows)
    {
        j = 0;
        fprintf(stderr, "map->rows: %ld\n", map->rows);
        while (j < map->cols)
        {
            
            fprintf(stderr, "map->cols: %ld\n", map->cols);
            if (map->grid[i][j] == 'P')
                map->player_count++;
            else if (map->grid[i][j] == 'C')
                map->collectible_count++;
            else if (map->grid[i][j] == 'E')
                map->exit_count++;
            fprintf(stderr, "map->grid[%ld][%ld]: %c\n", i, j, map->grid[i][j]);
            j++;
        }
        fprintf(stderr, "map->grid[%ld]: %s \n", i, map->grid[i]);
        i++;
    }
    check_walls(map);
    fprintf(stderr, "map walls checked %d\n", map->is_valid);
    fprintf(stderr, "player_count: %d, collectible_count: %d, exit_count: %d\n", map->player_count, map->collectible_count, map->exit_count);
    map->is_valid = (map->player_count == 1) && (map->collectible_count > 0) && (map->exit_count == 1) && (map->walls == 1) && (map->rect == 1);
    fprintf(stderr, "is_valid: %d\n", map->is_valid);
}
// void append_cords(cord_t **first, size_t x, size_t y)
// {
//     cord_t *new_cord;
//     cord_t *tmp;
//     new_cord = init_cord(new_cord);
//     if (new_cord == NULL)
//         return;
//     if (first == NULL)
//     {
//         *first = new_cord;
//     }
//     else
//     {
//         tmp = *first;
//         while (tmp->next != NULL)
//         {
//             tmp = tmp->next;
//         }
//         tmp->next = new_cord;
//     }
// }
void find_colect_cords(map_t *map)
{

    size_t i = 0;
    size_t j = 0;
    cord_t *new_cord;
    int count = map->collectible_count;
    fprintf(stderr, "count: %d\n", count);
    while (i < map->rows && count > 0)
    {
        fprintf(stderr, "map->grid[%ld][%ld]: %c\n", i, j, map->grid[i][j]);
        j = 0;
        while (j < map->cols && count > 0)
        {
            fprintf(stderr, "map->grid[%ld][%ld]: %c\n", i, j, map->grid[i][j]);
            if (map->grid[i][j] == 'C')
            {
                new_cord = init_cord(map->assets->colect->cord);
                if(new_cord == NULL)
                    return;
                new_cord->cord_x = i;
                new_cord->cord_y = j;
                map->assets->colect->cord = new_cord;
                fprintf(stderr, "YES_colect\n");
                count--;
                fprintf(stderr, "count: %d\n", count);
            }
            else if (map->grid[i][j] == 'E')
            {
                new_cord = init_cord(map->assets->enemy->cord);
                if(new_cord == NULL)
                    return;
                new_cord->cord_x = i;
                new_cord->cord_y = j;
                map->assets->enemy->cord = new_cord;
                fprintf(stderr, "YES_exit\n");
            }
            else if (map->grid[i][j] == 'P')
            {
                new_cord = init_cord(map->assets->player->cord);
                if(new_cord == NULL)
                    return;
                new_cord->cord_x = i;
                new_cord->cord_y = j;
                map->assets->player->cord = new_cord;
                fprintf(stderr, "YES_player\n");
            }
            else if (map->grid[i][j] == '1')
            {
                new_cord = init_cord(map->assets->env_front->cord);
                if(new_cord == NULL)
                    return;
                new_cord->cord_x = i;
                new_cord->cord_y = j;
                map->assets->env_front->cord = new_cord;
                fprintf(stderr, "YES_env_front\n");
            }
            else if (map->grid[i][j] == '0')
            {
                new_cord = init_cord(map->assets->env_back->cord);
                if(new_cord == NULL)
                    return;
                new_cord->cord_x = i;
                new_cord->cord_y = j;
                map->assets->env_back->cord = new_cord;
                fprintf(stderr, "YES_env_back\n");
            }
            
            j++;
        }
        i++;
    }
}
    


void map_pathfinder(map_t *map) 
{
    map->assets->colect->cord = NULL;
    map->assets->player->cord = NULL;
    map->assets->enemy->cord = NULL;
    map->assets->env_back->cord = NULL;
    map->assets->env_front->cord = NULL;
    
    fprintf(stderr, "2_cords adress: %p\n", map->assets->player->cord);
    find_colect_cords(map);
    cord_t *current = map->assets->colect->cord;
    while (current->next != NULL) {
    printf("Coordinate_colect: (%ld, %ld)\n", current->cord_x, current->cord_y);
    current = current->next;
    }
    cord_t *player = map->assets->player->cord;
    
    while (player->next != NULL) {
    printf("Coordinate_player: (%ld, %ld)\n", player->cord_x, player->cord_y);
    player = player->next;   
    }
    cord_t *exit = map->assets->enemy->cord;
    while (exit->next != NULL) {
    printf("Coordinate_exit: (%ld, %ld)\n", exit->cord_x, exit->cord_y);
    exit = exit->next;
    }
    cord_t *env_back = map->assets->env_back->cord;
    while (env_back->next != NULL) {
    printf("Coordinate_env_back: (%ld, %ld)\n", env_back->cord_x, env_back->cord_y);
    env_back = env_back->next;
    }
    cord_t *env_front = map->assets->env_front->cord;
    while (env_front->next != NULL) {
    printf("Coordinate_env_front: (%ld, %ld)\n", env_front->cord_x, env_front->cord_y);
    env_front = env_front->next;
}
    // find exit cords
    //find player cords
    
}

// map_t *init_map(char *path)
// {
//     map_t *map;

//     map = malloc(sizeof(map_t));
//     if (!map)
//     {
//         fprintf(stderr, "Failed to allocate memory for map\n");
//         return NULL;
//     }

//     map = load_map(path, map);
//     map_checks(map);
//     map_pathfinder(map);
//     fprintf(stderr, "map init map : %p\n", map);
//     return (map);
// }

// cord_t *init_cord(int x, int y)
// {
//     cord_t *cord;
//    // assets_t *assets;

//     cord = malloc(sizeof(cord_t));
//     if (!cord)
//     {
//         fprintf(stderr, "Failed to allocate memory for cord\n");
//         return NULL;
//     }
//     cord->cord_x = x;
//     cord->cord_y = y;

    
//     return (cord);
// }
void debug_env_front(assets_t *assets) {
    if (!assets || !assets->env_front) {
        fprintf(stderr, "env_front not initialized\n");
        return;
    }

    game_t *env_front = assets->env_front;

    if (!env_front->setup || !env_front->setup->complex || !env_front->setup->graph) {
        fprintf(stderr, "env_front substructures not initialized\n");
        return;
    }

    fprintf(stderr, "env_front Complex Data:\n");
    fprintf(stderr, "wave_amplitude: %f, wave_freq: %f, scale_fact: %f\n  color: %d\n",
            env_front->setup->complex->wave_amplitude,
            env_front->setup->complex->wave_freq,
            env_front->setup->complex->scale_fact,
            env_front->setup->graph->color);

    fprintf(stderr, "env_front Viewport Data:\n");
    fprintf(stderr, "Position: (%f, %f), Size: %d\n",
            env_front->setup->data->vp_position_x,
            env_front->setup->data->vp_position_y,
            env_front->setup->data->vp_size);
}
// Main function
int main() 
{
    mlx_t *mlx;
    mlx = init_mlx_session(WINDOW_WIDTH, WINDOW_HEIGHT, "Lost in Void");
    init_structures(mlx);


    // mlx_t *mlx;
    // assets_t *assets;
    // map_t *map;
    // cord_t *cord;
    // char *path = "map.ber";
    // size_t i = 0;
    // size_t j = 0;

    // mlx = init_mlx_session(WINDOW_WIDTH, WINDOW_HEIGHT, "Lost in Void");
    // assets = init_assets(mlx);
    // cord = init_cord(0, 0);
    // fprintf(stderr,"cord address: %p\n", cord);
    // map = init_map(path);
    // assets->colect->cord = cord;
    // assets->player->cord = cord;
    // assets->game->cord = cord;
    // assets->env_back->cord = cord;
    // assets->env_front->cord = cord;
    // assets->enemy->cord = cord;
  
    // i = 0;
    // while (i < map->rows) 
    // {
    //     j = 0;
    //     while (j < map->cols)
    //     {
    //         fprintf(stderr, "%c", map->grid[i][j]);
    //         j++;
    //     }
    //     map->grid[i][j] = '\0';
    //     fprintf(stderr, "\n");
    //     i++;
    // }
    // fprintf(stderr, "map->grid: %s\n", map->grid[1]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[2]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[3]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[4]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[5]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[6]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[7]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[8]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[9]);
    // fprintf(stderr, "map : %p\n", map);
    
    // debug_env_front(assets);
    // fprintf(stderr, "assets.env_front : %p\n", assets->env_front);
    // fprintf(stderr, "assets.env_back : %p\n", assets->env_back);
    // render(assets);
    // fprintf(stderr, "assets.env_front : %p\n", assets->env_front);
    // fprintf(stderr, "assets.env_back : %p\n", assets->env_back);

    mlx_terminate(mlx);
    return EXIT_SUCCESS;

  
   

}