/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:38:45 by mgavorni          #+#    #+#             */
/*   Updated: 2024/12/06 14:17:37 by mgavorni         ###   ########.fr       */
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
   // g->color = 0x007F7FFF;
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

    update_viewport(who->setup, thickness);
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
    assets->player = init_game();
    assets->env_front = init_game();
    assets->colect = init_game();
    assets->enemy = init_game();
    

    assets->game->setup->mlx = mlx;
    assets->env_back->setup->mlx = mlx;
    assets->player->setup->mlx = mlx;
    assets->env_front->setup->mlx = mlx;
    assets->colect->setup->mlx = mlx;
    assets->enemy->setup->mlx = mlx;
   

    custumizer_pass(assets);
    
    
    return (assets);
}


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
    update_viewport(assets->player->setup, 1);
    update_viewport(assets->game->setup, 1);
    update_viewport(assets->env_back->setup, 1);
    update_viewport(assets->env_front->setup, 1);
    update_viewport(assets->colect->setup, 1);
    update_viewport(assets->enemy->setup, 1);
    
}

void event_handler(mlx_key_data_t keydata, void *param)
{
    assets_t *assets = (assets_t *)param;
    key_hook(keydata, assets->player);
    
}
void def_map(map_t *map)
{
    map->grid = NULL;
    map->rows = 0;
    map->cols = 0;
    map->player_count = 0;
    map->collectible_count = 0;
    map->exit_count = 0;
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
                map->cols = ft_strlen(line);
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
map_t *init_map(char *path)
{
    map_t *map;

    map = malloc(sizeof(map_t));
    if (!map)
    {
        fprintf(stderr, "Failed to allocate memory for map\n");
        return NULL;
    }

    map = load_map(path, map);
    fprintf(stderr, "map init map : %p\n", map);
    return (map);
}
// Main function
int main() 
{
    mlx_t *mlx;
    assets_t *assets;
    map_t *map;
    char *path = "map.ber";
    size_t i = 0;
    size_t j = 0;

    mlx = init_mlx_session(WINDOW_WIDTH, WINDOW_HEIGHT, "Lost in Void");
    assets = init_assets(mlx);
    map = init_map(path);

    fprintf(stderr, "map->rows: %ld\n", map->rows);
    fprintf(stderr, "map->cols: %ld\n", map->cols);
    fprintf(stderr, "map->player_count: %d\n", map->player_count);
    fprintf(stderr, "map->collectible_count: %d\n", map->collectible_count);
    fprintf(stderr, "map->exit_count: %d\n", map->exit_count);
    fprintf(stderr, "map->is_valid: %d\n", map->is_valid);
    i = 0;
    while (i < map->rows) 
    {
        j = 0;
        while (j < map->cols)
        {
            fprintf(stderr, "%c", map->grid[i][j]);
            j++;
        }
        fprintf(stderr, "\n");
        i++;
    }
    // fprintf(stderr, "map->grid: %s\n", map->grid[1]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[2]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[3]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[4]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[5]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[6]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[7]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[8]);
    // fprintf(stderr, "map->grid: %s\n", map->grid[9]);
    fprintf(stderr, "map : %p\n", map);
    
  
    render(assets);
   
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
    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}