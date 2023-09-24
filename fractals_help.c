/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksenia <ksenia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:27:24 by ksenia            #+#    #+#             */
/*   Updated: 2023/09/24 15:20:54 by ksenia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_cell(t_params *params, u32 color, int x, int y)
{
	int	dx;
	int	dy;

	dx = 0;
	while (dx < params->downsampling)
	{
		dy = 0;
		while (dy < params->downsampling)
		{
			my_mlx_pixel_put(params->img, x + dx, y + dy, color);
			dy++;
		}
		dx++;
	}
}

void	draw_fractal(t_params *params, u32 (*fractal)(int, int, t_params *))
{
	int	x;
	int	y;
	u32	color;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			color = fractal(x, y, params);
			draw_cell(params, color, x, y);
			y += params->downsampling;
		}
		x += params->downsampling;
	}
}

void	choose_fractal(int argc, char *argv[], t_params *params)
{
	double	a3;
	double	a4;

	u32 (*fractal)(int x, int y, t_params * p);
	(void)argc;
	fractal = mandelbrot;
	if (ft_streq(argv[1], "mandelbrot") || (parse_double(argv[1])) == 1)
		fractal = mandelbrot;
	else if (ft_streq(argv[1], "julia") || ft_atoi(argv[1]) == 2)
	{
		a3 = parse_double(argv[2]);
		a4 = parse_double(argv[3]);
		if ((a3 != 0) & (a4 != 0))
		{
			params->julia_params.real = a3;
			params->julia_params.imag = a4;
		}
		fractal = julia;
	}
	else if (ft_streq(argv[1], "burningship") || ft_atoi(argv[1]) == 3)
		fractal = burningship;
	draw_fractal(params, fractal);
}

unsigned int	color(double value, t_params params)
{
	int	rg;

	if (value > 1.0)
		value = 1.0;
	if (value < 0)
		value = 0;
	if (value > 0.5)
	{
		return (color((value - 0.5) * 2, params));
	}
	rg = 255.0 * value * 2;
	return (rgb(params.color, rg, params.color - rg));
}

double	norm_complex(t_complex a)
{
	return (hypot(a.real, a.imag));
}
