/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 05:08:59 by galauren          #+#    #+#             */
/*   Updated: 2025/08/26 15:02:33 by galauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	end_it(t_philo_list *p)
{
	pthread_mutex_lock(&(p->tblptr->print_lock));
	pthread_mutex_lock(&(p->tblptr->death_lock));
	pthread_mutex_lock(&(p->tblptr->enough_lock));
	if (--p->tblptr->finished_count <= 0)
	{
		p->tblptr->stop_it = 1;
		printf("%ldms :\t[ %d ]%s\n",
			get_time_since_start(), p->id + 1, "Everybody Has Eaten YAY !");
	}
	pthread_mutex_unlock(&(p->tblptr->enough_lock));
	pthread_mutex_unlock(&(p->tblptr->death_lock));
	pthread_mutex_unlock(&(p->tblptr->print_lock));
}

void	eating(t_philo_list *p)
{
	sem_wait(p->forks);
	philo_status_print(p, "has taken a fork");
	sem_wait(p->forks);
	philo_status_print(p, "has taken a fork");
	pthread_mutex_lock(&(p->meal_lock));
	p->last_meal = get_time_since_start();
	pthread_mutex_unlock(&(p->meal_lock));
	philo_status_print(p, "is eating");
	smart_sleep(p, p->o.eat);
	sem_post(p->forks);
	sem_post(p->forks);
	if (p->o.has_meal_left && !--(p->o.meal_left))
	{
		p->i_should_stop = 1;
		end_it(p);
	}
}

void	sleeping(t_philo_list *p)
{
	philo_status_print(p, "is sleeping");
	smart_sleep(p, p->o.sleep);
}

void	thinking(t_philo_list *p)
{
	philo_status_print(p, "is thinking");
}
