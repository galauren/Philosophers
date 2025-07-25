/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:10:06 by galauren          #+#    #+#             */
/*   Updated: 2025/07/25 09:03:09 by galauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_status_print(t_philo_list *p, char *msg)
{	
	pthread_mutex_lock(&(p->tblptr->print_lock));
	pthread_mutex_lock(&(p->tblptr->death_lock));
	if (!p->tblptr->stop_it)
		printf("%ldms :\t[ %d ]%s\n", get_time_since_start(), p->id + 1, msg);
	pthread_mutex_unlock(&(p->tblptr->death_lock));
	pthread_mutex_unlock(&(p->tblptr->print_lock));
}

void	*philo_do(void *ptr)
{
	t_philo_list		*p;
	unsigned long long	now;

	p = (t_philo_list *)ptr;
	if (p->id % 2 == 1)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&(p->tblptr->death_lock));
		if (p->tblptr->stop_it)
		{
			pthread_mutex_unlock(&(p->tblptr->death_lock));
			break ;
		}	
		pthread_mutex_unlock(&(p->tblptr->death_lock));
		eating(p);
		sleeping(p);
		thinking(p);
	}
	return (NULL);
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
		ptr = ptr->next;
		++i;
	}
	return (0);
}

void	*the_great_judgment(void *table)
{
	t_table				*t;
	t_philo_list		*p;
	unsigned long long	now;

	t = (t_table *)table;
	while (1)
	{
		p = t->pop->next;
		while (p != t->pop)
		{
			pthread_mutex_lock(&(p->meal_lock));
			now = get_time_since_start();
			if (now - p->last_meal > t->o.die)
			{	
				pthread_mutex_unlock(&(p->meal_lock));
				philo_status_print(p, "Has reached his limits. May he now rest in peace.");
				pthread_mutex_lock(&(t->death_lock));
				t->stop_it = 1;
				pthread_mutex_unlock(&(t->death_lock));
			}
			else
				pthread_mutex_unlock(&(p->meal_lock));
			p = p->next;
		}
		usleep(1000);
	}
	return (NULL);
}

int	dinner_time(t_table *table)
{
	t_philo_list	*ptr;
	int				i;

	if (create_philo_threads(table->pop))
		return (1);
	if (pthread_create(&(table->j_thread), NULL, &the_great_judgment, table))
		return (printf("Error: Couldn't create the_great_judgment.\n"), 2);
	i = 0;
	ptr = table->pop->next;
	while (ptr != table->pop && ptr->id != -1)
	{
		if (pthread_join(ptr->thread, NULL))
			return (printf("Error: Couldn't join thread number %d\n", i), 2);
		ptr = ptr->next;
		++i;
	}
	if (pthread_detach(table->j_thread))
		return (printf("Error: Couldn't join the_great_judgment.\n"), 3);
	return (0);
}
