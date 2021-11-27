#include "f.h"

void	put_color(t_str *point, int color)
{
	point->i = (4 * 1000 * point->y_y) + point->x_x * 4;
	point->ch[point->i] = (point->iter * point->color + 535 + 179) * color;
	point->ch[point->i + 1] = (point->iter * point->color + 42 + 84) * color;
	point->ch[point->i + 2] = (point->iter * point->color + 535 + 45) * color;
	point->ch[point->i + 3] = 0;
}

void	zoom(t_str *point, double x, double y, double zoom)
{
	double	o_x;
	double	o_y;

	o_x = ((x / 1000) * (point->e_x - point->s_x)) + point->s_x;
	o_y = ((y / 600) * (point->e_y - point->s_y)) + point->s_y;
	point->s_x = o_x + ((point->s_x - o_x) * zoom);
	point->s_y = o_y + ((point->s_y - o_y) * zoom);
	point->e_y = o_y + ((point->e_y - o_y) * zoom);
	point->e_x = o_x + ((point->e_x - o_x) * zoom);
	if (point->max <= 120)
		point->max += 2;
}

void	julia(t_str *point)
{
	mlx_clear_window(point->mlx, point->win);
	point->y_y = 0;
	while (point->y_y < 600)
	{
		point->x_x = 0;
		while (point->x_x < 1000)
		{
			point->iter = 0;
			init_x_y(point);
			iter_loop(point);
			if (point->iter == point->max)
				put_color(point, 0);
			else
				put_color(point, 1);
			point->x_x++;
		}
		point->y_y++;
	}
	mlx_put_image_to_window(point->mlx, point->win, point->img, 0, 0);
	mlx_hook(point->win, 4, 1, m_press, point);
	mlx_hook(point->win, 6, 1, m_move, point);
	mlx_hook(point->win, 17, 1, exit_program, point);
	mlx_hook(point->win, 2, 1, k_press, point);
	mlx_loop(point->mlx);
}

void	map(t_str *point)
{
	point->x = point->x_x / (1000 / (point->e_x - point->s_x)) + point->s_x;
	point->y = point->y_y / (600 / (point->e_y - point->s_y)) + point->s_y;
	point->x_o = point->x;
	point->y_o = point->y;
}

void	mandelbrot(t_str *point)
{
	mlx_clear_window(point->mlx, point->win);
	point->y_y = 0;
	while (point->y_y < 600)
	{
		point->x_x = 0;
		while (point->x_x < 1000)
		{
			point->iter = 0;
			map(point);
			iter_loop(point);
			if (point->iter == point->max)
				put_color(point, 0);
			else
				put_color(point, 1);
			point->x_x++;
		}
		point->y_y++;
	}
	point->stop = 1;
	mlx_put_image_to_window(point->mlx, point->win, point->img, 0, 0);
	mlx_hook(point->win, 4, 1, m_press, point);
	mlx_hook(point->win, 6, 1, m_move, point);
	mlx_hook(point->win, 17, 1, exit_program, point);
	mlx_hook(point->win, 2, 1, k_press, point);
	mlx_loop(point->mlx);
}
