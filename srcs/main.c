/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <rsibiet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 13:25:36 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/04 13:35:23 by ksoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_philo	g_tp[7];
t_mlx	g_mlx;

static int		key_hook(int keycode, t_mlx *g_mlx)
{
	int			i;

	i = 0;
	(void)g_mlx;
	if (keycode == 53)
	{
		while (i < N_PHILO)
		{
			pthread_detach(g_tp[i].thread);
			++i;
		}
		exit(EXIT_SUCCESS);
	}
	return (0);
}

static void		dance(t_mlx *g_mlx)
{
	int		i;

	i = 0;
	mlx_string_put(g_mlx->ptr, g_mlx->win, WIDTH / 2 - 200,
		HEIGHT / 2 + 200, 0xFFFFFF, "Now, it is time... To DAAAAAAAANCE ! ! !");
}

static void		dead(t_mlx *g_mlx)
{
	int		i;

	i = 0;
	mlx_string_put(g_mlx->ptr, g_mlx->win, WIDTH / 2 - 200,
		HEIGHT / 2 + 200, 0xFFFFFF, "Un philosophe est mort... :/");
}

static int		main_loop(t_mlx *mlx)
{
	char			*path;
	static time_t	timestamp;
	static char		*pictures[8] = {
		"/imgs/Godwin.xpm",
		"/imgs/Lafayette.xpm",
		"/imgs/Tracy.xpm",
		"/imgs/Washington.xpm",
		"/imgs/Jefferson.xpm",
		"/imgs/Montesquieu.xpm",
		"/imgs/Voltaire.xpm",
		"/imgs/dance.xpm"
	};

	(void)mlx;
	if (timestamp == 0)
		timestamp = time(NULL);
	if ((path = getcwd(NULL, PATH_MAX)) == NULL)
		exit(EXIT_FAILURE);
	if (g_mlx.alive == 0 && g_mlx.time < TIMEOUT)
		dead(&g_mlx);
	else if ((g_mlx.time = time(NULL) - timestamp) >= TIMEOUT)
		dance(&g_mlx);
	else
		do_images(&g_mlx, pictures, path);
	return (0);
}

int				main(void)
{
	int		i;

	i = 0;
	init(&g_tp[0], &g_mlx);
	while (i < N_PHILO)
	{
		if (pthread_create(&g_tp[i].thread, NULL, enjoy, &g_tp[i]) != 0)
			exit(EXIT_FAILURE);
		++i;
	}
	mlx_hook(g_mlx.win, 2, 64, &key_hook, &g_mlx);
	mlx_loop_hook(g_mlx.ptr, &main_loop, &g_mlx);
	mlx_loop(g_mlx.ptr);
	return (EXIT_SUCCESS);
}
