#include "f.h"

void	put_image(t_str *point)
{
	int	a;
	int	b;

	b = -1;
	while (++b < 600)
	{
		a = 999;
		while (++a < 1000)
		{
			point->i = (b * 1000 * 4) + (a * 4);
			point->ch[point->i + 1] = 87;
			point->ch[point->i + 2] = 54;
			point->ch[point->i + 3] = 0;
		}
	}
	mlx_put_image_to_window(point->mlx, point->win, point->img, 0, 0);
}

void	iter_loop(t_str *point)
{
	while (point->iter < point->max)
	{
		point->x_t = point->x * point->x - point->y * point->y;
		point->y_t = 2 * point->x * point->y;
		point->x = point->x_t + point->x_o;
		point->y = point->y_t + point->y_o;
		if (point->x * point->x + point->y * point->y > 4)
			break ;
		point->iter++;
	}
}

void	init(t_str *point, char *str)
{
	point->s_x = -2;
	point->e_x = 2;
	point->s_y = -2;
	point->e_y = 2;
	point->x_o = -0.4;
	point->y_o = 0.6;
	point->zoom = 0;
	point->stop = 0;
	point->max = 40;
	point->color = 20;
	point->name = str;
}

void	check_fractol(t_str *point)
{
	if (ft_strcmp(point->name, "julia") == 0)
		julia(point);
	else if (ft_strcmp(point->name, "mandelbrot") == 0)
		mandelbrot(point);
	else
		write (1, "use: ./fractol [julia or mandelbrot]\n", 38);
}

int	main(int arg, char *argv[])
{
	t_str	p;

	if (arg > 2)
	{
		if (ft_strcmp(argv[1], "julia") == 0 || ft_strcmp(argv[1]
				, "mandelbrot") == 0)
		{
			p.mlx = mlx_init();
			p.win = mlx_new_window(p.mlx, 1000, 600, "uterese Fractol");
			p.img = mlx_new_image(p.mlx, 1000, 600);
			p.ch = mlx_get_data_addr(p.img, &p.bpp, &p.size, &p.end);
		}
		init(&p, argv[1]);
		check_fractol(&p);
	}
	else
	{
		write(1, "use: ./fractol [julia or mandelbrot]\n", 38);
	}
	return (0);
}
