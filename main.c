/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksenia <ksenia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:44:30 by ksenia            #+#    #+#             */
/*   Updated: 2023/09/24 14:08:56 by ksenia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

u32	rgb(u8 red, u8 green, u8 blue)
{
	u32	rgb;

	rgb = ((u32)red << 16) | ((u32)green << 8) | (u32)blue;
	return (rgb);
}

t_complex	get_compl_coord(int x, int y)
{
	t_complex	c;

	c.real = (double)(x - WIDTH / 2) / (WIDTH / 4);
	c.imag = (double)(y - HEIGHT / 2) / (WIDTH / 4);
	return (c);
}

unsigned int	point_color(double r, unsigned int color)
{
	if (isnan(r))
		return (0x000000);
	if (r > 10)
		return (0x000000);
	return (color);
}

int	on_destroy(void)
{
	exit(0);
	return (0);
}

int	on_keydown(int key, t_params *params)
{
	if (key == 'a')
		params->dx -= 0.5 * params->scale;
	if (key == 'd')
		params->dx += 0.5 * params->scale;
	if (key == 'w')
		params->dy -= 0.5 * params->scale;
	if (key == 's')
		params->dy += 0.5 * params->scale;
	if (key == 'q')
		params->scale *= 2;
	if (key == 'e')
		params->scale /= 2;
	if (key == '[')
		params->downsampling *= 2;
	if ((key == ']') && (params->downsampling > 1))
		params->downsampling /= 2;
	if (key == 65307)
		on_destroy();
	if (key == 'c')
		params->color = 128 + (params->color == 128) * 127;
	choose_fractal(params->argc, params->argv, params);
	mlx_put_image_to_window(params->mlx, params->mlx_win, params->img->img, 0,
		0);
	return (1);
}

double	parse_mantissa(char *s, int *dot, int *power)
{
	double	res;

	res = 0;
	while (*s)
	{
		if (*s == '.')
		{
			*dot += 1;
			s++;
			continue ;
		}
		if (dot)
			*power += 1;
		if (!ft_isdigit(*s))
			return (0);
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res);
}

double	parse_double(char *s)
{
	double	res;
	int		minus;
	int		power;
	int		dot;

	minus = 0;
	power = -1;
	dot = 0;
	if (*s == '-')
	{
		minus = 1;
		s++;
	}
	res = parse_mantissa(s, &dot, &power);
	if (dot > 1)
		return (0);
	while (power--)
		res /= 10.0;
	if (minus)
		return (-res);
	return (res);
}

int	mouse_event(int key, int x, int y, t_params *params)
{
	if (key == 4)
	{
		params->scale *= ADDSCALE;
	}
	else if (key == 5)
	{
		params->dx += (float)(x - WIDTH / 2) * (1 - 1 / ADDSCALE)
			* params->scale / (WIDTH / 4);
		params->dy += (float)(y - HEIGHT / 2) * (1 - 1 / ADDSCALE)
			* params->scale / (WIDTH / 4);
		params->scale /= ADDSCALE;
	}
	choose_fractal(params->argc, params->argv, params);
	mlx_put_image_to_window(params->mlx, params->mlx_win, params->img->img, 0,
		0);
	return (1);
}

void	init_params(t_params *params, t_data *img)
{
	params->scale = 1;
	params->dx = 0;
	params->dy = 0;
	params->downsampling = 8;
	params->color = 255;
	params->mlx = mlx_init();
	params->mlx_win = mlx_new_window(params->mlx, 1920, 1080, "fractal");
	params->img = img;
}

int	main(int argc, char **argv)
{
	t_data		img;
	t_params	params;

	params.argc = argc;
	params.argv = argv;
	init_params(&params, &img);
	mlx_hook(params.mlx_win, 2, 0b1, on_keydown, &params);
	mlx_mouse_hook(params.mlx_win, mouse_event, &params);
	mlx_hook(params.mlx_win, 17, 0b1, on_destroy, &params);
	img.img = mlx_new_image(params.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	choose_fractal(argc, argv, &params);
	usleep(100000);
	mlx_put_image_to_window(params.mlx, params.mlx_win, img.img, 0, 0);
	mlx_loop(params.mlx);
}
