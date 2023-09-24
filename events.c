/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksenia <ksenia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:10:24 by ksenia            #+#    #+#             */
/*   Updated: 2023/09/24 14:13:09 by ksenia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

int	mouse_event(int key, int x, int y, t_params *params)
{
	if (key == 4)
	{
		params->scale *= ADDSCALE;
	}
	else if (key == 5)
	{
		params->dx += (float)(x - WIDTH / 2) *(1 - 1 / ADDSCALE)
			* params->scale / (WIDTH / 4);
		params->dy += (float)(y - HEIGHT / 2) *(1 - 1 / ADDSCALE)
			* params->scale / (WIDTH / 4);
		params->scale /= ADDSCALE;
	}
	choose_fractal(params->argc, params->argv, params);
	mlx_put_image_to_window(params->mlx, params->mlx_win, params->img->img, 0,
		0);
	return (1);
}
