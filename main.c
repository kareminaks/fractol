#include"fractol.h"





void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int rgb(unsigned char red, unsigned char green, unsigned char blue)
{
	unsigned int rgb = ((unsigned int)red << 16) | ((unsigned int)green << 8) | (unsigned int)blue;
	return rgb;
}



t_complex get_compl_coord(int x, int y)
{
	t_complex c;
	c.real = (double)(x - WIDTH/2)/(WIDTH/4);
	c.imag = (double)(y-HEIGHT/2)/(WIDTH/4);
	return (c);
}

t_complex mult_complex(t_complex a, t_complex b)
{
	t_complex c;
	c.real = a.real*b.real - a.imag*b.imag;
	c.imag = a.real* b.imag + a. imag * b.real;
	return(c);
}


t_complex add_complex(t_complex a, t_complex b) 
{
	t_complex c;
	c.real = a.real+b.real;
	c.imag = a.imag + b.imag;

	return(c);
}

t_complex abs_complex(t_complex c)
{
    c.real = fabs(c.real);
    c.imag = fabs(c.imag);
    return(c);
}

double norm_complex(t_complex a) {
	return hypot(a.real, a.imag);
}

unsigned int point_color(double r,unsigned int color) {
	if (isnan(r)) 
			return 0x000000;
	
	if (r>10)
		return 0x000000;

	return color;
}


int max (int a, int b)
{
	if (a > b)
	return a;
	return b;
}




int on_keydown(int key, t_params* params) {
	if (key == 'a') params->dx -= 0.5 * params->scale;
	if (key == 'd') params->dx += 0.5 * params->scale;
	if (key == 'w') params->dy -= 0.5 * params->scale;
	if (key == 's') params->dy += 0.5 * params->scale;
	if (key == 'q') params->scale *= 2;
	if (key == 'e') params->scale /= 2;
	if (key == '[') params->downsampling*=2;
	if ((key == ']') && (params->downsampling > 1)) params->downsampling/=2;

	
	choose_fractal(params->argc, params->argv, params);

	mlx_put_image_to_window(params->mlx, params->mlx_win, params->img->img, 0, 0);
	return 1;
}

double parse_double(char* s) {
	double res = 0;
	int minus = 0;
	int power = 0;
	int dot = 0;

	if (*s == '-') {minus = 1; s++;}

	while(*s) {
		if (*s == '.') {
			dot++;
			s++;
			continue;
		}
		if (dot) power++;
		if (!ft_isdigit(*s)) return 0;

		res = res * 10 + (*s - '0');
		s++;
	}
	if (dot > 1) return 0;

	while(power--) res /= 10.0;

	if (minus) return -res;

	return res;
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	
	t_params params;
	params.scale = 1;
	params.dx = 0;
	params.dy = 0;
	params.argc = argc;
	params.argv = argv;
	params.downsampling = 8;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	params.mlx = mlx;
	params.mlx_win = mlx_win;
	params.img = &img;
	mlx_hook(mlx_win, 2, 0b1, on_keydown, &params);

	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    //ft_printf("line length: %d bpp=%d \n", img.line_length, img.bits_per_pixel);

	choose_fractal(argc, argv, &params);
	usleep(100000);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
