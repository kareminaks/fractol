/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksenia <ksenia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:11:35 by ksenia            #+#    #+#             */
/*   Updated: 2023/09/24 14:36:47 by ksenia           ###   ########.fr       */
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

t_complex	get_compl_coord(int x, int y, t_params* params)
{
	t_complex	c;

	c.real = (double)(x - WIDTH / 2) / (WIDTH / 4);
	c.imag = (double)(y - HEIGHT / 2) / (WIDTH / 4);
	c.real *= params->scale;
	c.imag *= params->scale;
	c.real += params->dx;
	c.imag += params->dy;
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
