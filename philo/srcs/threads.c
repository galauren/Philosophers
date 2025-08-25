/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:10:06 by galauren          #+#    #+#             */
/*   Updated: 2025/08/25 23:01:40 by galauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_do(void *ptr)
{
	t_philo_list		*p;

	p = (t_philo_list *)ptr;
	if (get_time_in_ms() < p->tblptr->start)
		micro_sleeps(p->tblptr->start - get_time_in_ms());
	if (p->tblptr->o.philo_nb == 1)
		return (print_the_lonely_prompt(p));
	if ((unsigned)p->id % 2 == 0 && !((unsigned)p->id + 1 == p->tblptr->o.philo_nb
			&& p->tblptr->o.philo_nb % 2 == 1))
		usleep(200);
	while (1)
	{
		if (p->i_should_stop)
			return (NULL);
		pthread_mutex_lock(&(p->tblptr->death_lock));
		if (p->tblptr->stop_it)
			return (pthread_mutex_unlock(&(p->tblptr->death_lock)), NULL);
		pthread_mutex_unlock(&(p->tblptr->death_lock));
		eating(p);
		sleeping(p);
		thinking(p);
		usleep(500);
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

void	*check_philos(t_table *t, t_philo_list *p)
{
	unsigned long long	now;

	pthread_mutex_lock(&(p->meal_lock));
	now = get_time_since_start();
	if (now - p->last_meal > t->o.die)
	{	
		pthread_mutex_unlock(&(p->meal_lock));
		philo_status_print(p,
			"Has reached his limits. May he now rest in peace.");
		pthread_mutex_lock(&(t->death_lock));
		t->stop_it = 1;
		pthread_mutex_unlock(&(t->death_lock));
		return (NULL);
	}
	else
		pthread_mutex_unlock(&(p->meal_lock));
	return (NULL);
}

void	*the_great_judgment(void *table)
{
	t_table				*t;
	t_philo_list		*p;

	t = (t_table *)table;
	if (get_time_in_ms() < t->start)
		micro_sleeps(t->start - get_time_in_ms());
	while (1)
	{
		p = t->pop->next;
		while (p != t->pop)
		{
			usleep(1);
			check_philos(t, p);
			if (get_stop(p))
				return (NULL);
			p = p->next;
		}
		usleep(500);
	}
	return (NULL);
}

int	dinner_time(t_table *table)
{
	t_philo_list	*ptr;
	int				i;

	if (pthread_create(&(table->j_thread), NULL, &the_great_judgment, table))
		return (printf("Error: Couldn't create the_great_judgment.\n"), 2);
	if (create_philo_threads(table->pop))
		return (3);
	i = 0;
	ptr = table->pop->next;
	if (pthread_join(table->j_thread, NULL))
		return (printf("Error: Couldn't join the_great_judgment.\n"), 4);
	while (ptr != table->pop && ptr->id != -1)
	{
		if (pthread_join(ptr->thread, NULL))
			return (printf("Error: Couldn't join thread number %d\n", i), 5);
		ptr = ptr->next;
		++i;
	}
	return (0);
}
