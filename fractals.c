/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksenia <ksenia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:27:24 by ksenia            #+#    #+#             */
/*   Updated: 2023/09/24 14:34:34 by ksenia           ###   ########.fr       */
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
	u32		(*fractal)(int, int, t_params *);
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
		else
		{
			params->julia_params.real = 1.0;
			params->julia_params.imag = 0.5;
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

unsigned int	mandelbrot(int x, int y, t_params *params)
{
	t_complex	p;
	int			i;
	t_complex	c;
	double		distance;
	t_complex	next;
	double		kek;
	double		d;

	p = get_compl_coord(x, y);
	p.real *= params->scale;
	p.imag *= params->scale;
	p.real += params->dx;
	p.imag += params->dy;
	i = 0;
	c = p;
	while (i < MANDELBROT_MAX_I)
	{
		next = add_complex(mult_complex(c, c), p);
		distance = hypot(next.real, next.imag);
		if (isnan(module(next)) || (distance > MANDELBROT_RADIUS))
		{
			break ;
		}
		c = next;
		i++;
	}
	i = max(MANDELBROT_MAX_I - i, 0);
	if (i == MANDELBROT_MAX_I)
		return (0xffffff);
	kek = (double)i / (double)MANDELBROT_MAX_I;
	d = module(c) / MANDELBROT_RADIUS;
	return (color((kek * 31 - d) / 32, *params));
}

unsigned int	julia(int x, int y, t_params *params)
{
	t_complex	c;
	t_complex	p;
	int			i;
	double		first;
	double		dist;

	c = get_compl_coord(x, y);
	c.real *= params->scale;
	c.imag *= params->scale;
	c.real += params->dx;
	c.imag += params->dy;
	p = c;
	i = 0;
	while (i < JULIA_MAX_I)
	{
		p = c;
		c = add_complex(mult_complex(c, c), params->julia_params);
		i++;
		if (hypot(c.real, c.imag) > 100)
			break ;
	}
	first = (double)(i) / (double)(JULIA_MAX_I);
	first = 1.0 - first;
	dist = hypot(p.real, p.imag) / 100;
	if (isnan(dist))
		dist = 1.0;
	return (color((first * 31 + dist) / 32, *params));
}

unsigned int	burningship(int x, int y, t_params *params)
{
	const double radius = 100;
	t_complex p = get_compl_coord(x, y);
	p.real *= params->scale;
	p.imag *= params->scale;
	p.real += params->dx;
	p.imag += params->dy;
	int i = 0;

	t_complex c = p;
	double distance;

	const int max_i = 256;
	while (i < max_i)
	{
		t_complex next;
		next = add_complex(mult_complex(abs_complex(c), abs_complex(c)), p);
		distance = hypot(next.real, next.imag);
		if (isnan(module(next)) || (distance > radius))
		{
			break ;
		}
		c = next;
		i++;
	}

	i = max(max_i - i, 0);
	if (i == max_i)
		return (0xffffff);
	double kek = (double)i / (double)max_i;
	double d = module(c) / radius;

	return (color((kek * 31 - d) / 32, *params));
}