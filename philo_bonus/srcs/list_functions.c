/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 21:48:39 by glaurent          #+#    #+#             */
/*   Updated: 2025/08/26 16:35:31 by galauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	erase_forks_and_philos(t_table *table)
{
	t_philo_list	*current;
	t_philo_list	*next;
	int				i;

	i = -1;
	if (table->forks)
		sem_destroy(table->forks);
	table->forks = NULL;
	if (!table->pop)
		return ;
	current = table->pop->next;
	while (current && current != table->pop)
	{
		next = current->next;
		if (!pthread_mutex_lock(&(current->meal_lock)))
			if (!pthread_mutex_unlock(&(current->meal_lock)))
				pthread_mutex_destroy(&(current->meal_lock));
		free(current);
		current = next;
	}
	free(table->pop);
}

void	erase_table(t_table *table)
{
	if (!table)
		return ;
	if (!pthread_mutex_lock(&(table->print_lock)))
		if (!pthread_mutex_unlock(&(table->print_lock)))
			pthread_mutex_destroy(&(table->print_lock));
	if (!pthread_mutex_lock(&(table->death_lock)))
		if (!pthread_mutex_unlock(&(table->death_lock)))
			pthread_mutex_destroy(&(table->death_lock));
	if (!pthread_mutex_lock(&(table->enough_lock)))
		if (!pthread_mutex_unlock(&(table->enough_lock)))
			pthread_mutex_destroy(&(table->enough_lock));
	erase_forks_and_philos(table);
}

t_philo_list	*add_philo(int id, t_table *table)
{
	t_philo_list	*root;
	t_philo_list	*new;

	root = table->pop;
	if (!root || root->id != -1)
		return (NULL);
	new = malloc(sizeof(t_philo_list));
	if (new != NULL)
	{
		new->id = id;
		new->last_meal = 0;
		new->i_should_stop = 0;
		new->o = table->o;
		new->forks = table->forks;
		if (pthread_mutex_init(&(new->meal_lock), NULL))
			return (NULL);
		new->prev = root->prev;
		new->next = root;
		root->prev->next = new;
		root->prev = new;
		new->tblptr = table;
	}
	return (new);
}

t_table	*create_forks_and_philos(t_table *table, unsigned int nb)
{
	unsigned int	i;
	static sem_t	semaphore;

	if (nb > 5000)
		return (table);
	if (sem_init(&semaphore, 0, nb) == -1)
		return (erase_table(table), NULL);
	table->forks = &semaphore;
	i = 0;
	while (i < nb)
	{
		if (!add_philo(i, table))
			return (erase_table(table),
				sem_destroy(table->forks), NULL);
		i++;
	}
	return (table);
}

t_table	*create_table(t_table *table, t_options o)
{
	t_philo_list	*philo_root;

	if (pthread_mutex_init(&(table->print_lock), NULL))
		return (erase_table(table), NULL);
	if (pthread_mutex_init(&(table->death_lock), NULL))
		return (erase_table(table), NULL);
	if (pthread_mutex_init(&(table->enough_lock), NULL))
		return (erase_table(table), NULL);
	philo_root = malloc(sizeof(t_philo_list));
	if (philo_root == NULL)
		return (erase_table(table), NULL);
	philo_root->id = -1;
	philo_root->o = o;
	philo_root->last_meal = table->start;
	philo_root->forks = NULL;
	philo_root->prev = philo_root;
	philo_root->next = philo_root;
	philo_root->tblptr = table;
	table->stop_it = 0;
	table->o = o;
	table->pop = philo_root;
	if (!create_forks_and_philos(table, o.philo_nb))
		return (NULL);
	return (table);
}
