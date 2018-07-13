/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoulard <ksoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 10:54:10 by ksoulard          #+#    #+#             */
/*   Updated: 2017/05/04 13:34:23 by ksoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int			do_think_with_minebag(t_philo *ph, time_t *timealive)
{
	ph->stats = 0;
	ph->stats = THINK_M;
	while (*timealive + THINK_T > time(NULL))
	{
		usleep(1000);
		if (is_critical(ph) == 0 && do_eat(ph, timealive) != -1)
		{
			ph->lastcall = 1;
			return (-1);
		}
		if (ph->callme == 1)
			break ;
	}
	pthread_mutex_unlock(&ph->mutex);
	ph->stats = 0;
	return (0);
}

static int			do_think_with_rightbag(t_philo *ph, time_t *timealive)
{
	if (!(ph->right->stats & EAT_M))
	{
		ph->right->callme = 1;
		pthread_mutex_unlock(&ph->right->mutex);
	}
	if (pthread_mutex_trylock(&ph->right->mutex) == 0)
	{
		ph->stats = THINK_M;
		while (*timealive + THINK_T > time(NULL))
		{
			usleep(1000);
			if (is_critical(ph) == 0 && do_eat(ph, timealive) != -1)
			{
				ph->lastcall = 1;
				return (-1);
			}
			if (ph->right->callme == 1)
				break ;
		}
		pthread_mutex_unlock(&ph->right->mutex);
		ph->right->callme = 0;
		ph->stats = 0;
		return (0);
	}
	return (-1);
}

int					do_think(t_philo *ph, time_t *timealive)
{
	if (!(ph->left->stats & EAT_M))
		pthread_mutex_unlock(&ph->mutex);
	if (pthread_mutex_trylock(&ph->mutex) == 0)
		return (do_think_with_minebag(ph, timealive));
	else
		return (do_think_with_rightbag(ph, timealive));
	return (0);
}
