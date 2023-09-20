#ifndef FRACTOL_H
# define FRACTOL_H

#include "libft/libft.h"
#include <mlx.h>
#include"math.h"
#include "stdio.h"


#define WIDTH 1920
#define HEIGHT 1080


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct complex{
double real;
double imag;
}t_complex;

typedef struct params {
	double dx;
	double dy;
	double scale;

	void* mlx;
	void* mlx_win;
	t_data* img;

    int argc;
    char** argv;
	 

	int downsampling;
}	t_params;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
unsigned int rgb(unsigned char red, unsigned char green, unsigned char blue);
t_complex get_compl_coord(int x, int y);
t_complex mult_complex(t_complex a, t_complex b);
t_complex add_complex(t_complex a, t_complex b);
unsigned int point_color(double r,unsigned int color);
int max (int a, int b);
unsigned int mandelbrot(int x, int y, t_params* params);
int on_keydown(int key, t_params* params);
void choose_fractal(int argc,char *argv[], t_params *params);
unsigned int julia(int x, int y, t_params* params, t_complex julia);
double parse_double(char* s);
t_complex abs_complex(t_complex c);
unsigned int burningship(int x, int y, t_params* params);
double module(t_complex c);
int ft_streq(char* a, char* b);
t_complex mult_complex(t_complex a, t_complex b);
t_complex add_complex(t_complex a, t_complex b);
t_complex abs_complex(t_complex c);
double norm_complex(t_complex a);
int max (int a, int b);


#endif