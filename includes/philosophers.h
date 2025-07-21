/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:54:12 by galauren          #+#    #+#             */
/*   Updated: 2025/07/20 16:49:32 by galauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_options
{
	unsigned int	philo_nb;
	unsigned int	die;
	unsigned int	eat;
	unsigned int	sleep;
	unsigned int	meal_left;
	int				has_meal_left;
}	t_options;

typedef struct s_philo_list
{
	int					id;
	pthread_t			thread;
	unsigned long		last_meal;
	t_options			o;
	pthread_mutex_t		*l_fork;				
	pthread_mutex_t		*r_fork;				
	pthread_mutex_t		speaking;				
	pthread_mutex_t		checking;				
	struct s_philo_list	*prev;
	struct s_philo_list	*next;
}	t_philo_list;

typedef struct s_table
{
	t_options		o;
	t_philo_list	*pop;
	pthread_mutex_t	*forks;
	unsigned long	start;
	char			stop;
}	t_table;

/*
**-------------------------------------
**
**                UTILS			  
**
**-------------------------------------
*/

double			ft_strtod(const char *s);
unsigned long	get_time_in_ms(void);

/*
 /-------------------------------\
  \								/
  /\		      LISTS		   /\
 /  \					      /  \
\---------------------------------/
*/

t_table			*create_table(t_table *table, t_options o);
void			erase_table(t_table *table, int forks_to_free);

#endif
