/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 21:48:39 by glaurent          #+#    #+#             */
/*   Updated: 2025/07/20 16:49:55 by galauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	erase_table(t_table *table, int forks_to_free)
{
	t_philo_list	*current;
	t_philo_list	*next;
	int		i;

	if (!table)
		return ;
	i = -1;
	while (++i < forks_to_free)
	{
		pthread_mutex_destroy(&(table->forks[i]));
	}
	free(table->forks);
	table->forks = NULL;
	if (!table->pop)
		return ;
	current = table->pop->next;
	while (current && current != table->pop)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(table->pop);
	table->pop = NULL;
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
		new->last_meal = table->start;
		new->o = table->o;
		new->l_fork = &(table->forks[id]);
		new->r_fork = &(table->forks[(id + 1) % table->o.philo_nb]);
		new->prev = root->prev;
		new->next = root;
		root->prev->next = new;
		root->prev = new;
	}
	return (new);
}

t_table	*create_forks_and_philos(t_table *table, unsigned int nb)
{
	unsigned int	i;

	i = 0;
	while(i < nb)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			return (erase_table(table, i), NULL);
		i++;
	}
	i = 0;
	while(i < nb)
	{
		if (!add_philo(i, table))
			return (erase_table(table, table->o.philo_nb), NULL);
		i++;
	}
	return (table);
}

t_table	*create_table(t_table *table, t_options o)
{
	t_philo_list	*philo_root;

	philo_root = malloc(sizeof(t_philo_list));
	if (philo_root == NULL)
		return (NULL);
	philo_root->id = -1;
	philo_root->last_meal = table->start;
	philo_root->o = o;
	philo_root->l_fork = NULL;
	philo_root->r_fork = NULL;
	philo_root->prev = philo_root;
	philo_root->next = philo_root;
	table->o = o;
	table->pop = philo_root;	
	table->forks = malloc(sizeof(pthread_mutex_t) * o.philo_nb);
	if (table->forks == NULL)
		return (free(philo_root), NULL);
	table->stop = 0;
	if (!create_forks_and_philos(table, o.philo_nb))
		return (free(philo_root), free(table->forks), NULL);
	return (table);
}


