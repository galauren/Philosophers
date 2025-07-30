/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galauren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:54:12 by galauren          #+#    #+#             */
/*   Updated: 2025/07/30 06:38:32 by galauren         ###   ########.fr       */
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

typedef struct s_table t_table;

typedef struct s_philo_list
{
	int					id;
	pthread_t			thread;
	unsigned long long	last_meal;
	t_options			o;
	pthread_mutex_t		*l_fork;				
	pthread_mutex_t		*r_fork;				
	pthread_mutex_t		meal_lock;				
	struct s_philo_list	*prev;
	struct s_philo_list	*next;
	t_table				*tblptr;
	int					i_should_stop;
}	t_philo_list;

typedef struct s_table
{
	t_options			o;
	t_philo_list		*pop;
	pthread_t			j_thread;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;				
	pthread_mutex_t		death_lock;				
	pthread_mutex_t		enough_lock;				
	unsigned long long	start;
	char				stop_it;
	unsigned int		finished_count;
}	t_table;

/*
 /-------------------------------\
  \								/
  /\		   ALGO 		   /\
 /  \					      /  \
\---------------------------------/
*/

int				dinner_time(t_table *table);
void			eating(t_philo_list *p);
void			sleeping(t_philo_list *p);
void			thinking(t_philo_list *p);

/*
**--------------------------------
**
**             UTILS			  
**
**--------------------------------
*/

double			ft_strtod(const char *s);
unsigned long	get_time_in_ms(void);
unsigned long	get_time_since_start(void);
void			micro_sleeps(unsigned long duration);
void			smart_sleep(t_philo_list *p, unsigned long duration);
void			philo_status_print(t_philo_list *p, char *msg);
void			*print_too_much_prompt(t_philo_list *p);

/*
 /-------------------------------\
  \								/
  /\	       LISTS		   /\
 /  \					      /  \
\---------------------------------/
*/

t_table			*create_table(t_table *table, t_options o);
void			erase_table(t_table *table, int forks_to_free);

#endif
