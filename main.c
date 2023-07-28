#include"fractol.h"

#define WIDTH 1920
#define HEIGHT 1080

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int rgb(unsigned char red, unsigned char green, unsigned char blue)
{
	unsigned int rgb = ((unsigned int)red << 16) + ((unsigned int)green << 8) + blue;
	return (rgb);
}
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	unsigned char color;
	float distance;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    //ft_printf("line length: %d bpp=%d \n", img.line_length, img.bits_per_pixel);

    for(int x=0;x<=1920;x++) {
        for(int y=0;y<=1080;y++) {
			distance = (float)(x+y)/(float)(WIDTH+HEIGHT)*255.0;
			color = 0xFF - (unsigned int)(distance);
            my_mlx_pixel_put(&img, x, y, rgb(color,color, color));
        }
    }
	usleep(100000);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

