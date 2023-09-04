#include "stdio.h"
#include"math.h"
#include"fractol.h"


#define WIDTH 1920
#define HEIGHT 1080


t_complex mult_complex(t_complex a, t_complex b)
{
	t_complex c;
	c.real = a.real*b.real - a.imag*b.imag;
	c.imag = a.real* b.imag + a. imag * b.real;
	return(c);
}

t_complex abs_complex(t_complex c)
{
    c.real = fabs(c.real);
    c.imag = fabs(c.imag);
    return(c);
}

t_complex add_complex(t_complex a, t_complex b) 
{
	t_complex c;
	c.real = a.real+b.real;
	c.imag = a.imag + b.imag;

	return(c);
}

t_complex get_compl_coord(int x, int y)
{
	t_complex c;
	c.real = (double)(x - WIDTH/2)/(WIDTH/4);
	c.imag = (double)(y-HEIGHT/2)/(WIDTH/4);
	return (c);
}

double module(t_complex c) {
	return hypot(c.real, c.imag);
}

#include "string.h"

    int main(void)
	{
    int n =0;
	int arr[36];
    const double radius = 1000;
    const int max_i = 256;
    int i;
        
    int i_hist[max_i+2];
    memset(i_hist, 0, (max_i+2)*sizeof(int));
    memset(arr, 0, (36)*sizeof(int));

    for(int x=0;x<=1920;x++) {
    for(int y=0;y<=1080;y++) {
        t_complex p = get_compl_coord(x,y);
        t_complex c = p;
	    double distance;
        i = 0;
	    while (i++<max_i)
	    {
            t_complex next = add_complex(mult_complex(c,c),p);
            distance = hypot(next.real, next.imag);
            if (isnan(module(next)) || (distance > radius)) {
                break;
            }
            c = next;
        }
        distance = hypot(c.real, c.imag);
        if (i == max_i) distance = 0;
        arr[(int)(distance)/32]++;
        i_hist[i-1]++;
	
    }
    }
    for(int i=0;i<36;i++) printf("%d\n", arr[i]);
    for(int i=0;i<=max_i;i++) printf("%d ", i_hist[i]);
    return 0;
    }
