/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksenia <ksenia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:16:01 by ksenia            #+#    #+#             */
/*   Updated: 2023/09/24 14:16:26 by ksenia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	norm_complex(t_complex a)
{
	return (hypot(a.real, a.imag));
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
