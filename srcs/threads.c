/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:10:06 by galauren          #+#    #+#             */
/*   Updated: 2025/07/23 04:15:48 by galauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_status_print(t_philo_list *p, char *msg)
{	
	pthread_mutex_lock(&(p->tblptr->print_lock));
	pthread_mutex_lock(&(p->tblptr->death_lock));
	if (!p->stop_it)
		printf("%ldms :\t[ %d ]%s\n", get_time_since_start(), p->id + 1, msg);
	pthread_mutex_unlock(&(p->tblptr->death_lock));
	pthread_mutex_unlock(&(p->tblptr->print_lock));
}

void	*philo_do(void *ptr)
{
	t_philo_list	*p;

	p = (t_philo_list *)ptr;

	philo_status_print(p, "Is Thinking...");
/*	while (1)
	{
			
	}
*/	return (NULL);
}

int	create_philo_threads(t_philo_list *philo)
{
	t_philo_list	*ptr;
	int				i;

	i = 0;
	ptr = philo->next;
	while (ptr != philo && ptr->id != -1)
	{
		if (pthread_create(&(ptr->thread), NULL, &philo_do, ptr))
			return (printf("Error: Couldn't create thread number %d\n", i), 1);
		if (pthread_join(ptr->thread, NULL))
			return (printf("Error: Couldn't join thread number %d\n", i), 2);
		ptr = ptr->next;
		++i;
	}
	return (0);
}

int	dinner_time(t_table *table)
{
	if (create_philo_threads(table->pop))
		return (1);
	return (0);
}
