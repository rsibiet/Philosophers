/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoulard <ksoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 10:54:09 by ksoulard          #+#    #+#             */
/*   Updated: 2017/05/04 12:39:14 by ksoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int		eat(t_philo *ph, time_t *timealive)
{
	ph->stats = EAT_M;
	time(timealive);
	while (*timealive + EAT_T > time(NULL))
		;
	pthread_mutex_unlock(&ph->mutex);
	pthread_mutex_unlock(&ph->right->mutex);
	ph->life = MAX_LIFE;
	time(timealive);
	ph->callme = 0;
	ph->right->callme = 0;
	ph->stats = 0;
	return (0);
}

int				do_eat(t_philo *ph, time_t *timealive)
{
	if ((ph->left->stats & EAT_M) != 0 || (ph->right->stats & EAT_M) != 0)
		return (-1);
	ph->callme = 1;
	ph->right->callme = 1;
	if ((ph->right->stats & THINK_M))
		pthread_mutex_unlock(&ph->right->mutex);
	if (trylocks(ph, M_MUTEX | R_MUTEX) == 0)
		return (eat(ph, timealive));
	ph->callme = 0;
	ph->right->callme = 0;
	ph->stats = 0;
	return (-1);
}
