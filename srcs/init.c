/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoulard <ksoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:44:56 by ksoulard          #+#    #+#             */
/*   Updated: 2017/05/04 10:58:15 by ksoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void		init(t_philo *tp, t_mlx *g_mlx)
{
	int		i;

	i = 0;
	while (i < N_PHILO)
	{
		tp[i].life = MAX_LIFE;
		tp[i].thread = 0;
		tp[i].callme = 0;
		tp[i].lastcall = 0;
		tp[i].mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		tp[i].n = i;
		if (i == 0)
			tp[i].left = &tp[6];
		else
			tp[i].left = &tp[i - 1];
		if (i < 6)
			tp[i].right = &tp[i + 1];
		else
			tp[i].right = &tp[0];
		i++;
	}
	g_mlx->alive = 1;
	g_mlx->ptr = mlx_init();
	g_mlx->win = mlx_new_window(g_mlx->ptr, WIDTH, HEIGHT, "PHILOSOPHERS");
}
