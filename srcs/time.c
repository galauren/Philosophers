/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:37:02 by galauren          #+#    #+#             */
/*   Updated: 2025/07/27 07:47:53 by galauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_time_in_ms(void)
{
	struct timeval	tv;
	long			milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_sec * 1000L) + tv.tv_usec / 1000L;
	return ((unsigned long)milliseconds);
}
unsigned long get_time_since_start(void)
{
	static unsigned long	start = 0;
	unsigned long			now;

	if (start == 0)
		start = get_time_in_ms() + 1000;
	now = get_time_in_ms();
	return (now - start);
}

int	get_stop(t_philo_list *p)
{
	char	res;
	
	pthread_mutex_lock(&(p->tblptr->death_lock));
	res = p->tblptr->stop_it;
	pthread_mutex_unlock(&(p->tblptr->death_lock));
	return ((int)res);
}

void	smart_sleep(t_philo_list *p, unsigned long duration)
{
	unsigned long	start;

	start = get_time_in_ms();
	while (!get_stop(p) && get_time_in_ms() - start < duration)
	{
		usleep(250);
	}
}

void	micro_sleeps(unsigned long duration)
{
	unsigned long	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < duration)
	{
		usleep(250);
	}
}
