/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksenia <ksenia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:44:30 by ksenia            #+#    #+#             */
/*   Updated: 2023/09/24 15:04:45 by ksenia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
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
	params->julia_params.real = 1.0;
	params->julia_params.imag = 0.5;
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
