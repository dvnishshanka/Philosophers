#ifndef PHILO_H
# define PHILO_H

# define ERROR_CODE -2147483647

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;

typedef enum mtx_state {
	MTX_INIT,
	MTX_LOCK,
	MTX_UNLOCK,
	MTX_DESTROY,
} t_mtx_state;

typedef struct s_fork {
	t_mtx	fork;
	int		fork_id;
} t_fork;

typedef struct s_philo
{
	int	id;
	int	meals_counter;
	int is_full;
	long last_meal_time;	// time passed from last meal
	t_fork	*left_fork;
	t_fork	*right_fork;
	pthread_t	thread_id;
	t_table	*table;
}	t_philo;

struct s_table {
	int nbr_philo;
	long	time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int nbr_limit_meals;
	long start_simulation;
	int is_end_simulation;
	t_fork	*forks; // array of forks
	t_philo	*philos; // array of philosophers
} ;


// Prototypes
long error_exit(const char *error_msg);
long	parse_input(t_table *table, char **argv);

#endif