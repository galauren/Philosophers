/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:37:02 by galauren          #+#    #+#             */
/*   Updated: 2025/07/23 06:54:06 by galauren         ###   ########.fr       */
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
		start = get_time_in_ms();
	now = get_time_in_ms();
	return (now - start);
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
