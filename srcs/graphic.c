/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoulard <ksoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 10:58:51 by ksoulard          #+#    #+#             */
/*   Updated: 2017/05/04 13:34:57 by ksoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void		put_background(t_mlx *g_mlx, char *path)
{
	char			*lname;
	int				size[2];

	if ((lname = ft_strjoin(path, "/imgs/ROOM4.xpm")) == NULL)
		return ;
	g_mlx->img = mlx_xpm_file_to_image(g_mlx->ptr, lname, &size[0], &size[1]);
	if (g_mlx->img != NULL)
		mlx_put_image_to_window(g_mlx->ptr, g_mlx->win, g_mlx->img, 0, 0);
	ft_strdel(&lname);
}

static void		put_state(t_mlx *g_mlx, int x, int pos)
{
	static t_states	states[3] = {
		{"I'm eating ! :)", EAT_M, 0xFF0000, "2 STICKS"},
		{"I'm thinking :D", THINK_M, 0x00FF00, "1 STICK"},
		{"I'm resting :/", REST_M, 0x0000FF, "0 STICK"}
	};
	int				i;

	i = 0;
	while (i < 3)
	{
		if ((g_tp[pos].stats & states[i].mask) != 0)
		{
			mlx_string_put(g_mlx->ptr, g_mlx->win, x + 10, HEIGHT / 2 + 30,
				states[i].color, states[i].status);
			mlx_string_put(g_mlx->ptr, g_mlx->win, x + 10, HEIGHT / 2 + 50,
				0xFFFFFF, states[i].stick);
			break ;
		}
		++i;
	}
}

static void		put_images(t_mlx *g_mlx, int pos, char *path, char *name)
{
	int				x;
	int				size[2];
	char			*long_name;
	char			*life;
	char			*timer;

	if (pos == 0)
		put_background(g_mlx, path);
	long_name = ft_strjoin(path, name);
	if ((g_mlx->img = mlx_xpm_file_to_image(g_mlx->ptr, long_name,
		&size[0], &size[1])) == NULL)
		return ;
	x = pos * WIDTH / N_PHILO + size[1] / 10;
	life = ft_itoa(g_tp[pos].life);
	timer = ft_itoa(TIMEOUT - g_mlx->time);
	mlx_put_image_to_window(g_mlx->ptr, g_mlx->win, g_mlx->img, x, IMGPOS);
	mlx_string_put(g_mlx->ptr, g_mlx->win, x + 10, IMGPOS + 10, 0xCCCCFF, life);
	*ft_strrchr(long_name, '.') = '\0';
	mlx_string_put(g_mlx->ptr, g_mlx->win, x + 10, IMGPOS - 20, 0xFFFFFF,
		ft_strrchr(long_name, '/') + 1);
	mlx_string_put(g_mlx->ptr, g_mlx->win, 15, 10, 0xFFFFFF, timer);
	put_state(g_mlx, x, pos);
	ft_strdel(&long_name);
	ft_strdel(&life);
	ft_strdel(&timer);
}

void			do_images(t_mlx *g_mlx, char **pictures, char *path)
{
	int		i;

	i = 0;
	mlx_clear_window(g_mlx->ptr, g_mlx->win);
	while (i < N_PHILO)
	{
		put_images(g_mlx, i, path, pictures[i]);
		++i;
	}
	ft_strdel(&path);
}
