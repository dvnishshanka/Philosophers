/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnishsha <dnishsha@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:03:47 by dnishsha          #+#    #+#             */
/*   Updated: 2024/01/09 14:03:50 by dnishsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERROR_CODE -2147483647

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef enum mtx_state {
	MTX_INIT,
	MTX_LOCK,
	MTX_UNLOCK,
	MTX_DESTROY,
}	t_mtx_state;

typedef enum thread_state {
	THREAD_CREATE,
	THREAD_DETACH,
	THREAD_JOIN,
}	t_thread_state;

typedef struct s_fork {
	t_mtx	fork;
	int		fork_id;
}	t_fork;

// long		last_meal_time -> time passed from last meal
typedef struct s_philo
{
	int			id;
	int			meals_counter;
	int			is_full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

// t_fork	*forks -> array of forks
// t_philo	*philos -> array of philosophers
struct s_table {
	int		nbr_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		nbr_limit_meals;
	long	start_simulation;
	int		is_end_simulation;
	t_fork	*forks;
	t_philo	*philos;
} ;

// Prototypes
long	error_exit(const char *error_msg);
void	free_all(t_table *table);
long long	get_timestamp_in_ms(struct	timeval	*tv);
long	safe_mutex_handle(t_mtx *mutex, t_mtx_state mtx_state);
long	safe_pthread_handle(pthread_t *thread,
	void *(*start_routine) (void *), void *arg, t_thread_state thread_state);
long	parse_input(t_table *table, char **argv);
long	data_init(t_table *table);
int		dinner(t_table *table);

// Test functions
void	print_philos(t_philo *philos);
#endif
