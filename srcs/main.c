/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:46:44 by galauren          #+#    #+#             */
/*   Updated: 2025/08/07 14:04:26 by galauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	check_argument(char *arg)
{
	double	tmp;

	tmp = ft_strtod(arg);
	if (tmp == NAN || !(tmp >= 0.0 && tmp / (double)UINT_MAX <= 1))
		return (0);
	return ((unsigned int)tmp);
}

t_options	*set_program(int ac, char **av, t_options *o)
{
	double	tmp;

	o->philo_nb = check_argument(av[1]);
	o->die = check_argument(av[2]);
	o->eat = check_argument(av[3]);
	o->sleep = check_argument(av[4]);
	o->meal_left = 0;
	o->has_meal_left = 0;
	if (ac == 6)
	{
		o->has_meal_left = 1;
		tmp = ft_strtod(av[5]);
		if (tmp == NAN || !(tmp >= 0.0 && tmp / (double)UINT_MAX <= 1))
			return (printf("'The nummber of Meals left' has not been set correctly.\n"), NULL);
		o->meal_left = (unsigned int)tmp;
		if (o->meal_left == 0)
			return (printf("0 meal_left ? then let's just stop it before initializing.\n"), NULL);
	}
	if (o->philo_nb == 0
		|| o->die == 0
		|| o->eat == 0
		|| o->sleep == 0)
		return (printf("One argument is 0 or not an Unsigned Int\n"), NULL);
	return (o);
}

int	init_prog(int ac, char **av, t_options *o)
{
	if (!(ac >= 5 && ac <= 6))
		return (printf("Usage: ./philosophers   [number_of_philosophers]\n\
			[time_to_die]\n\
			[time_to_eat]\n\
			[time_to_sleep]\n\
			(number_of_times_each_philosopher_must_eat)\n"), 0);
	if (set_program(ac, av, o) == NULL)
		return (0);
	return (1);
}

void	print_philoinit(t_options o)
{
	char	*wtff;
	char	*la_decision;

	wtff = " ????????????????";
	la_decision = " ";
	if (o.philo_nb == 1 || o.philo_nb > 5000)
		la_decision = wtff;
	printf("\n			[number_of_philosophers] : %u %s\n\
			[time_to_die] : %u\n\
			[time_to_eat] : %u\n\
			[time_to_sleep] : %u\n\
			(number_of_times_each_philosopher_must_eat) : %u(%s)\n\n\n\n",
				o.philo_nb, la_decision, o.die, o.eat, o.sleep, o.meal_left,
				o.has_meal_left ? "set" : "unset");
}

int	main(int ac, char **av)
{
	t_options	o;
	t_table		table;

	table.pop = NULL;
	table.forks = NULL;
	if (init_prog(ac, av, &o) == 0)
		return (printf("Couldn't initiate program.\n"), 1);
	print_philoinit(o);
	get_time_since_start();
	table.start = get_time_in_ms() + 1000;
	table.finished_count = o.philo_nb;
	if (create_table(&table, o) == NULL)
		return (printf("Couldn't create table.\n"), 2);
	if (o.philo_nb > 5000)
	{
		micro_sleeps(1000);
		print_too_much_prompt(table.pop);
		return (erase_table(&table, 0), 3);
	}
	else if (dinner_time(&table))
	{
		printf("The dinner had to stop unexpectedly.\n");
		return (erase_table(&table, o.philo_nb), 4);
	}
	return (erase_table(&table, o.philo_nb), 0);
}
