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
	return (table);
}

void	add_head(int id, t_philo_list *root)
{
	t_philo_list	*new;

	new = malloc(sizeof(*new));
	if (new != NULL)
	{
		new->id = id;
		new->prev = root;
		new->next = root->next;
		root->next->prev = new;
		root->next = new;
	}
}
/*
	int				countdown;

	i = 0;
	while(i < table->o.philo_nb)
	{
		add_tail()
*/
void	add_tail(int id, t_table *table)
{
	t_philo_list	*new;

	new = malloc(sizeof(t_philo_list));
	if (new != NULL)
	{
		new->id = id;
		new->last_meal = table->start;
		new->o = table->o;
		new->l_fork = &table->forks[id];
		new->r_fork = &table->forks[(id + 1) % table->o.philo_nb];
		new->prev = root->prev;
		new->next = root;
		root->prev->next = new;
		root->prev = new;
	}
}

int	get_list_length(t_philo_list *a)
{
	t_philo_list	*tmp;
	int				i;

	tmp = a->next;
	i = 0;
	while (tmp != a)
	{
		tmp = tmp->next;
		++i;
	}
	return (i);
}
