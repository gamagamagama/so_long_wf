gcc viewport.c -o pixel -I../MLX42/include -L../MLX42/build/ -lmlx42 -lglfw -pthread -lm -ldl
gcc math_pa.c init.c -o pixel -I../MLX42/include -L../MLX42/build/ -lmlx42 -lglfw -pthread -lm -ldl