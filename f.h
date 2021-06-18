#ifndef F_H
# define F_H

# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_struct
{
	char	*ch;
	double	x;
	double	y;
	double	x_x;
	double	y_y;
	double	x_o;
	double	y_o;
	double	x_t;
	double	y_t;
	int		iter;
	void	*mlx;
	void	*win;
	void	*img;
	int		size;
	int		bpp;
	int		end;
	int		i;
	char	*name;
	double	s_y;
	double	e_y;
	double	s_x;
	double	e_x;
	int		zoom;
	int		stop;
	int		max;
	int		color;
}	t_str;

int		ft_strcmp(char *s1, char *s2);
void	init_x_y(t_str *point);
int		k_press(int k_c, t_str *point);
int		m_move(int x, int y, t_str *point);
int		m_press(int button, int x, int y, t_str *point);
void	zoom(t_str *point, double x, double y, double zoom);
void	julia(t_str *point);
void	map(t_str *point);
void	mandelbrot(t_str *point);
void	put_image(t_str *point);
void	iter_loop(t_str *point);
void	check_fractol(t_str *point);
void	put_color(t_str *point, int color);

#endif
