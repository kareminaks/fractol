#include "fractol.h"

void	choose_fractal(int argc, char *argv[], t_params *params)
{
	unsigned int	color;
	t_complex		julia_params;
	double			a3;
	double			a4;

	(void)argc;
	if (ft_streq(argv[1], "mandelbrot") || (parse_double(argv[1])) == 1)
	{
		for (int x = 0; x <= 1920; x += params->downsampling)
		{
			for (int y = 0; y <= 1080; y += params->downsampling)
			{
				color = mandelbrot(x, y, params);
				for (int dx = 0; dx < params->downsampling; dx++)
					for (int dy = 0; dy < params->downsampling; dy++)
						my_mlx_pixel_put(params->img, x + dx, y + dy, color);
			}
		}
	}
	else if (ft_streq(argv[1], "julia") || ft_atoi(argv[1]) == 2)
	{
		a3 = parse_double(argv[2]);
		a4 = parse_double(argv[3]);
		printf("a3=%f a4=%f\n", a3, a4);
		if ((a3 != 0) & (a4 != 0))
		{
			julia_params.real = a3;
			julia_params.imag = a4;
		}
		else
		{
			julia_params.real = 1.0;
			julia_params.imag = 0.5;
		}
		for (int x = 0; x <= 1920; x++)
		{
			for (int y = 0; y <= 1080; y++)
			{
				color = julia(x, y, params, julia_params);
				my_mlx_pixel_put(params->img, x, y, color);
			}
		}
	}
	else if (ft_streq(argv[1], "burningship") || ft_atoi(argv[1]) == 3)
	{
		for (int x = 0; x <= 1920; x++)
		{
			for (int y = 0; y <= 1080; y++)
			{
				color = burningship(x, y, params);
				my_mlx_pixel_put(params->img, x, y, color);
			}
		}
	}
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
	// int blue = (int)((1.0 - value) * 255.0);
	rg = 255.0 * value * 2;
	return (rgb(params.color, rg, params.color - rg));
}

unsigned int	mandelbrot(int x, int y, t_params *params)
{
	const double	radius;
	t_complex		p;
	int				i;
	t_complex		c;
	double			distance;
	const int		max_i;
	t_complex		next;
	double			kek;
	double			d;

	radius = 100;
	p = get_compl_coord(x, y);
	p.real *= params->scale;
	p.imag *= params->scale;
	p.real += params->dx;
	p.imag += params->dy;
	i = 0;
	c = p;
	max_i = 256;
	while (i < max_i)
	{
		next = add_complex(mult_complex(c, c), p);
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
	kek = (double)i / (double)max_i;
	d = module(c) / radius;
	return (color((kek * 31 - d) / 32, *params));
}

unsigned int	julia(int x, int y, t_params *params, t_complex julia)
{
	t_complex	c;
	t_complex	p;
	int			i;
	const int	max_i;
	double		first;
	double		dist;

	c = get_compl_coord(x, y);
	c.real *= params->scale;
	c.imag *= params->scale;
	c.real += params->dx;
	c.imag += params->dy;
	p = c;
	i = 0;
	max_i = 128;
	while (i < max_i)
	{
		p = c;
		c = add_complex(mult_complex(c, c), julia);
		i++;
		if (hypot(c.real, c.imag) > 100)
			break ;
	}
	first = (double)(i) / (double)(max_i);
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