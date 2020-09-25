#include "minirt.h"
	
	
	
int	gamma_corrected(int color, double one_over_gamma)
{
	t_fcolor	rgb;

	rgb = int_to_fcolor(color);

	rgb.red = pow(rgb.red, one_over_gamma);
	rgb.green = pow(rgb.green, one_over_gamma);
	rgb.blue = pow(rgb.blue, one_over_gamma);
	
	return (fcolor_to_int(rgb));
}
#ifdef USING_SDL
	void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
	{
		Uint32 *pixels = (Uint32 *)surface ->pixels;
		pixels[y * surface->w + x] = pixel;
	}

	void sdl_init_win(t_scene scene)
	{
		g_sdl_win.screen = NULL;
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError() ) ;
		else
			g_sdl_win.window = SDL_CreateWindow( "Raytracing in a bad language", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scene.resolution.x, scene.resolution.y, SDL_WINDOW_SHOWN);
		g_sdl_win.screen = SDL_GetWindowSurface(g_sdl_win.window);
	}

	void	sdl_render_frame(t_vect **ray_table, t_scene scene, t_point start, t_r_stack stack)
	{
		int	i;
		int	j;
		int color;
		double one_over_gamma;

		one_over_gamma = 1 / SCREEN_GAMMA;
		i = -1;
		while (++i < scene.resolution.y)
		{
			j = -1;
			while (++j < scene.resolution.x)
			{
				color = trace_ray(ray_table[i][j], scene, start, -1, 0, stack);
				put_pixel32(g_sdl_win.screen, j, i, gamma_corrected(color, one_over_gamma));
			}
		}
		SDL_UpdateWindowSurface(g_sdl_win.window);
	}
#endif

void	init_win(t_scene scene)
{
	#ifndef USING_SDL
		mlx_init_win(scene);
	#endif
	#ifdef USING_SDL
		sdl_init_win(scene);
	#endif
}

void	render_frame(t_vect **ray_table, t_scene scene, t_point start, t_r_stack stack)
{
	#ifndef USING_SDL
		mlx_render_frame(ray_table, scene, start, stack);
	#endif
	#ifdef USING_SDL
		sdl_render_frame(ray_table, scene, start, stack);
	#endif
}

#ifndef USING_SDL
	int	interact(int keycode, void *thing)
	{
		thing = 0;
		ft_putnbr_fd(keycode, 1);
		ft_putchar_fd('\n', 1);
		if (keycode == 53)
			exit(0);
		return (0);
	}

	void	mlx_init_win(t_scene scene)
	{
		g_win.mlx = mlx_init();
		g_win.win = mlx_new_window(g_win.mlx, scene.resolution.y, WIN_WIDTH, "miniRT");
		g_win.img = mlx_new_image(g_win.mlx, scene.resolution.x, WIN_WIDTH);
		g_win.buffer = (int*)mlx_get_data_addr(g_win.img, &g_win.bpp, &g_win.s_l, &g_win.endian);
	}

	void	mlx_render_frame(t_vect **ray_table, t_scene scene, t_point start, t_r_stack stack)
	{
		int	i;
		int	j;
		int color;
		double one_over_gamma;

		one_over_gamma = 1 / SCREEN_GAMMA;
		i = -1;
		while (++i < scene.resolution.y)
		{
			j = -1;
			while (++j < scene.resolution.x)
			{
				color = trace_ray(ray_table[i][j], scene, start, -1, 0, stack);
				g_win.buffer[j + i * scene.resolution.y] = gamma_corrected(color, one_over_gamma);
			}
		}
		mlx_put_image_to_window(g_win.mlx, g_win.win, g_win.img, 0, 0);
	}
#endif