/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoulard <ksoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:44:57 by ksoulard          #+#    #+#             */
/*   Updated: 2017/05/04 13:34:36 by ksoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int				is_critical(t_philo *ph)
{
	if (ph->life <= N_PHILO / 2)
		return (0);
	return (1);
}

int				trylocks(t_philo *ph, int mask)
{
	if (mask & M_MUTEX)
	{
		if (pthread_mutex_trylock(&ph->mutex) != 0)
			return (-1);
	}
	if (mask & R_MUTEX)
	{
		if (pthread_mutex_trylock(&ph->right->mutex) != 0)
		{
			pthread_mutex_unlock(&ph->mutex);
			return (-1);
		}
	}
	return (0);
}

void			*enjoy(void *var)
{
	time_t		lifetime;
	t_philo		*ph;

	ph = (t_philo *)var;
	time(&lifetime);
	while (42)
	{
		if (ph->lastcall != 1 && do_eat(ph, &lifetime) != -1)
			ph->lastcall = 1;
		else if (ph->lastcall != 2 && do_rest(ph, &lifetime) != -1)
			ph->lastcall = 2;
		else if (ph->lastcall != 3 && do_think(ph, &lifetime) != -1)
			ph->lastcall = 3;
		if ((ph->life -= time(NULL) - lifetime) <= 0)
		{
			g_mlx.alive = 0;
			return ((void *)NULL);
		}
		time(&lifetime);
	}
	return ((void *)NULL);
}
