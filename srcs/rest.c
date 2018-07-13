/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoulard <ksoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 10:54:12 by ksoulard          #+#    #+#             */
/*   Updated: 2017/05/04 13:35:09 by ksoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int			do_rest(t_philo *ph, time_t *timealive)
{
	ph->stats = 0;
	ph->stats = REST_M;
	time(timealive);
	while (*timealive + THINK_T > time(NULL))
	{
		if (is_critical(ph) == 0 && do_eat(ph, timealive) != -1)
		{
			ph->lastcall = 1;
			return (-1);
		}
		usleep(833);
	}
	ph->stats = 0;
	return (0);
}
