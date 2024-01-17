/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnishsha <dnishsha@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:03:47 by dnishsha          #+#    #+#             */
/*   Updated: 2024/01/17 13:12:15 by dnishsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERROR_CODE -2147483647
# define DEBUG_MODE 0

# define COLOR_BLUE "\033[0;34m"
# define COLOR_RED "\033[0;31m"
# define COLOR_RESET "\x1b[0m"

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

typedef enum philo_state {
	TOOK_FIRST_FORK,
	TOOK_SECOND_FORK,
	THINK,
	EAT,
	SLEEP,
	DIED,
}	t_philo_state;

typedef enum time_state {
	MILLISEC,
	MICROSEC,
}	t_time_state;

typedef struct s_fork {
	t_mtx	fork;
	int		fork_id;
}	t_fork;

// long		last_meal_time -> time passed from last meal
// mtx_philo -> This is useful for races with thread monitor
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
	t_mtx		mtx_philo;
}	t_philo;

// t_fork	*forks -> array of forks
// t_philo	*philos -> array of philosophers
struct s_table {
	int			nbr_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			nbr_limit_meals;
	long		start_simulation;
	int			is_end_simulation;
	int			all_threads_ready;
	t_mtx		mtx_table;
	t_mtx		mtx_write;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	monitor;
} ;

// Prototypes
// util functions
long	error_exit(const char *error_msg);
void	clean_all(t_table *table);
void	free_philos_tables(t_table *table);
void	wait_till_threads_ready(t_table	*table);
long	get_timestamp(t_time_state t_state);
void	sleep_with_interruption(long sleep_time, t_table *table);

// safe functions
long	safe_mutex_handle(t_mtx *mutex, t_mtx_state mtx_state);
long	safe_pthread_handle(pthread_t *thread,
			void *(*start_routine) (void *),
			void *arg, t_thread_state thread_state);
int		create_phil_thread(t_table *table);

long	parse_input(t_table *table, char **argv);
long	data_init(t_table *table);
int		dinner(t_table *table);
void	*dinner_simulation(void *arg);

//getters and seters
void	set_int(t_mtx *mutex, int *dest, int val);
int		get_int(t_mtx *mutex, int *val);
void	set_long(t_mtx *mutex, long *dest, long val);
long	get_long(t_mtx *mutex, long *val);
int		simulation_finished(t_table *table);

// Write functions
void	write_state(t_philo_state state, t_table *table, t_philo *philo);

// Monitor Function
void	*monitor_philos(void *arg);
#endif
