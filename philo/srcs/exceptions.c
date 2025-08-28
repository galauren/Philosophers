/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:37:42 by galauren          #+#    #+#             */
/*   Updated: 2025/08/28 05:32:36 by galauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_status_print(t_philo_list *p, char *msg)
{	
	pthread_mutex_lock(&(p->tblptr->print_lock));
	pthread_mutex_lock(&(p->tblptr->death_lock));
	pthread_mutex_lock(&(p->tblptr->enough_lock));
	if (!p->tblptr->stop_it)
		printf("%ld %d %s\n", get_time_since_start(), p->id + 1, msg);
	pthread_mutex_unlock(&(p->tblptr->enough_lock));
	pthread_mutex_unlock(&(p->tblptr->death_lock));
	pthread_mutex_unlock(&(p->tblptr->print_lock));
}

void	*print_too_much_prompt(t_philo_list *p)
{
	philo_status_print(p, " Some were trying desperatly to breath\n");
	philo_status_print(p, " Others were rushing at the central plate thinking \
\"I must eat before they do, or I might die tonight\".\n");
	philo_status_print(p, " Well not too much of a surprise right ?\n");
	philo_status_print(p, " You have to realise what you just did i guess\n");
	pthread_mutex_lock(&(p->tblptr->print_lock));
	pthread_mutex_lock(&(p->tblptr->death_lock));
	if (!p->tblptr->stop_it)
		printf("%ldms :\t[ %d ]Like really ?  %d ?!\n\n\n",
			get_time_since_start(), p->id + 1, p->tblptr->o.philo_nb);
	pthread_mutex_unlock(&(p->tblptr->death_lock));
	pthread_mutex_unlock(&(p->tblptr->print_lock));
	philo_status_print(p,
		"I fear your next command, honestly.\n");
	philo_status_print(p,
		"Next time try with less or equal than \e[33m5000 philosophers.\e[0m\n");
	smart_sleep(p, p->o.die);
	philo_status_print(p, "Oh and they are all dead you should know this\n");
	philo_status_print(p, "You are very welcome, again.\n");
	return (NULL);
}

void	*print_the_lonely_prompt(t_philo_list *p)
{
	int	loop_nb;

	philo_status_print(p, "\"One\" knew his situation you know ? \
\"Only one fork ?? Hell yeeeah\" he said...");
	philo_status_print(p, "");
	philo_status_print(p, "But you know, this guy is not crazy, \
he just though you know, \"there has to be someone coming to this dinner !\"");
	philo_status_print(p, "");
	philo_status_print(p, "But eventually winter came, \
and his friends - what am i even saying -");
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
