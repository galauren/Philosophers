/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:10:06 by galauren          #+#    #+#             */
/*   Updated: 2025/07/27 11:29:46 by galauren         ###   ########.fr       */
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

void	*print_too_much_prompt(t_philo_list *p)
{
	int	loop_nb;

	philo_status_print(p, " Some were trying desperatly to breath\n");
	philo_status_print(p, " Others were rushing at the central plate thinking \"I must eat before they do, or I might die tonight\".\n");
	philo_status_print(p, " Well not too much of a surprise right ?\n");
	philo_status_print(p, " You have to realise what you just did i guess\n");
	philo_status_print(p, " In the meantime could you check how much philosophers you wanted around that dinner table please ?\n\n\n");
	pthread_mutex_lock(&(p->tblptr->print_lock));
	pthread_mutex_lock(&(p->tblptr->death_lock));
	if (!p->tblptr->stop_it)
		printf("%ldms :\t[ %d ]  %d ?\n\n\n", get_time_since_start(), p->id + 1, p->tblptr->o.philo_nb);
	pthread_mutex_unlock(&(p->tblptr->death_lock));
	pthread_mutex_unlock(&(p->tblptr->print_lock));
	philo_status_print(p, "I feel like something has got out of hand so ill just leave\n");
	philo_status_print(p, "Next time try with less or equal to 5000 philosophers.\n");
	smart_sleep(p, p->o.die);
	philo_status_print(p, "Oh and they are all dead you should know this\n");
	philo_status_print(p, "You are very welcome, again.\n");
	return (NULL);
}

void	*print_the_lonely_prompt(t_philo_list *p)
{
	int	loop_nb;

	philo_status_print(p, "\"One\" knew his situation you know ? \"Only one fork ?? Hell yeeeah\" he said...");
	philo_status_print(p, "");
	philo_status_print(p, "But you know, this guy is not crazy, he just though you know, \"there has to be someone coming to this dinner !\"");
	philo_status_print(p, "");
	philo_status_print(p, "But eventually winter came, and his friends - what am i even saying -");
	philo_status_print(p, "");
	philo_status_print(p, "The dudes that were supposed to come never did.");
	philo_status_print(p, "");
	philo_status_print(p, "And you might have something to do with that...");
	philo_status_print(p, "");
	philo_status_print(p, "You are a terrible game master.");
	loop_nb = 30;
	while (loop_nb-- > 0)
		philo_status_print(p, "");
	smart_sleep(p, p->o.die);
	philo_status_print(p, "Oh he's dead by the way");
	philo_status_print(p, "");
	philo_status_print(p, "You are very welcome.");
	return (NULL);
}

void	*philo_do(void *ptr)
{
	t_philo_list		*p;
	unsigned long long	now;

	p = (t_philo_list *)ptr;
	if (get_time_in_ms() < p->tblptr->start)
		micro_sleeps(p->tblptr->start - get_time_in_ms());
	if (p->tblptr->o.philo_nb == 1)
		return (print_the_lonely_prompt(p));
	if (p->id % 2 == 0)
		usleep(200);
	while (1)
	{
		usleep(1);
		pthread_mutex_lock(&(p->tblptr->death_lock));
		if (p->tblptr->stop_it)
			return (pthread_mutex_unlock(&(p->tblptr->death_lock)), NULL);
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
	if (get_time_in_ms() < t->start)
		micro_sleeps(t->start - get_time_in_ms());
	while (1)
	{
		p = t->pop->next;
		while (p != t->pop)
		{
			usleep(1);
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

	if (pthread_create(&(table->j_thread), NULL, &the_great_judgment, table))
		return (printf("Error: Couldn't create the_great_judgment.\n"), 2);
	if (pthread_detach(table->j_thread))
		return (printf("Error: Couldn't join the_great_judgment.\n"), 3);
	create_philo_threads(table->pop);
	i = 0;
	ptr = table->pop->next;
	while (ptr != table->pop && ptr->id != -1)
	{
		if (pthread_join(ptr->thread, NULL))
			return (printf("Error: Couldn't join thread number %d\n", i), 2);
		ptr = ptr->next;
		++i;
	}
	return (0);
}
