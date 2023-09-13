#include"fractol.h"


double module(t_complex c) {
	return hypot(c.real, c.imag);
}


int ft_streq(char* a, char* b) {
    while(*a && *b && *a == *b) {
        a++;
        b++;
    }
    return *a == *b;
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

int max (int a, int b)
{
	if (a > b)
	return a;
	return b;
}
