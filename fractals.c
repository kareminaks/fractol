/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksenia <ksenia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:13:06 by ksenia            #+#    #+#             */
/*   Updated: 2023/09/24 15:19:17 by ksenia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	mandelbrot(int x, int y, t_params *params)
{
	t_complex	p;
	int			i;
	t_complex	c;
	t_complex	next;
	double		kek;

	p = get_compl_coord(x, y, params);
	i = 0;
	c = p;
	while (i < MANDELBROT_MAX_I)
	{
		next = add_complex(mult_complex(c, c), p);
		if (isnan(module(next)) || (hypot(next.real,
					next.imag) > MANDELBROT_RADIUS))
			break ;
		c = next;
		i++;
	}
	i = max(MANDELBROT_MAX_I - i, 0);
	if (i == MANDELBROT_MAX_I)
		return (0xffffff);
	kek = (double)i / (double)MANDELBROT_MAX_I;
	return (color((kek * 31 - module(c) / MANDELBROT_RADIUS) / 32, *params));
}

unsigned int	julia(int x, int y, t_params *params)
{
	t_complex	c;
	t_complex	p;
	int			i;
	double		first;
	double		dist;

	c = get_compl_coord(x, y, params);
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
	t_complex	p;
	int			i;
	t_complex	c;
	t_complex	next;
	double		kek;

	p = get_compl_coord(x, y, params);
	i = 0;
	c = p;
	while (i < BURNINGSHIP_MAX_I)
	{
		next = add_complex(mult_complex(abs_complex(c), abs_complex(c)), p);
		if (isnan(module(next)) || hypot(next.real,
				next.imag) > BURNINGSHIP_RADIUS)
			break ;
		c = next;
		i++;
	}
	i = max(BURNINGSHIP_MAX_I - i, 0);
	if (i == BURNINGSHIP_MAX_I)
		return (0xffffff);
	kek = (double)i / (double)BURNINGSHIP_MAX_I;
	return (color((kek * 31 - (module(c) / BURNINGSHIP_RADIUS)) / 32, *params));
}
