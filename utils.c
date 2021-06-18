#include "f.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	init_x_y(t_str *p)
{
	p->x = ((p->x_x / (double)1000) * (p->e_x - p->s_x)) + p->s_x;
	p->y = ((p->y_y / (double)600) * (p->e_y - p->s_y)) + p->s_y;
}

int	k_press(int k_c, t_str *point)
{
	if (k_c == 53)
	{
		mlx_destroy_image(point->mlx, point->img);
		mlx_destroy_window(point->mlx, point->win);
		free(point->mlx);
		exit(0);
	}
	return (0);
}

int	m_move(int x, int y, t_str *p)
{
	if (x < 1000 && y < 600 && p->stop == 0 && ft_strcmp(p->name, "julia") == 0)
	{
		p->x_o = (((double)x / 1000) * 4) - 2;
		p->y_o = ((((double)y * -1) / 600) * 4) + 2;
		check_fractol(p);
	}
	return (1);
}

int	m_press(int button, int x, int y, t_str *point)
{
	if (button == 5 && point->stop == 1)
		zoom(point, (double)x, (double)y, 1.1);
	else if (button == 4 && point->stop == 1)
		zoom(point, (double)x, (double)y, 0.9);
	check_fractol(point);
	return (1);
}
