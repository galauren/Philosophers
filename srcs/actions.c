/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 05:08:59 by galauren          #+#    #+#             */
/*   Updated: 2025/07/25 09:14:24 by galauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	end_it(t_philo_list *p)
{
	pthread_mutex_lock(&(p->tblptr->death_lock));
	p->tblptr->stop_it = 1;
	pthread_mutex_unlock(&(p->tblptr->death_lock));
}

void	eating(t_philo_list *p)
{
	if (p->o.has_meal_left)
	{
		if (!(p->o.meal_left)--)
		{
			end_it(p);
			return ;
		}
	}
	pthread_mutex_lock(p->l_fork);
	philo_status_print(p, "has taken a fork.");
	pthread_mutex_lock(p->r_fork);
	philo_status_print(p, "has taken a fork.");
	pthread_mutex_lock(&(p->meal_lock));
	p->last_meal = get_time_since_start();
	pthread_mutex_unlock(&(p->meal_lock));
	philo_status_print(p, "is eating...");
	micro_sleeps(p->o.eat);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}

void	sleeping(t_philo_list *p)
{
	philo_status_print(p, "is sleeping...");
	micro_sleeps(p->o.sleep);
}

void	thinking(t_philo_list *p)
{
	philo_status_print(p, "is thinking...");
}
