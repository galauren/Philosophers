/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:37:02 by galauren          #+#    #+#             */
/*   Updated: 2025/07/13 00:50:18 by galauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long get_time_in_ms(void)
{
	struct timeval	tv;
	long			milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_sec * 1000L) + tv.tv_usec / 1000L;
	return ((unsigned long)milliseconds);
}
/*
int main()
{
	unsigned long	actual;

	actual = get_time_in_ms();
	printf("%zu\n", get_time_in_ms() - actual);
	printf("%zu\n", get_time_in_ms() - actual);
	printf("%zu\n", get_time_in_ms() - actual);
	usleep(100);
	printf("%zu\n", get_time_in_ms() - actual);
	usleep(1000);
	printf("%zu\n", get_time_in_ms() - actual);
	usleep(10000);
	printf("%zu\n", get_time_in_ms() - actual);
	usleep(100000);
	printf("%zu\n", get_time_in_ms() - actual);
}
*/
