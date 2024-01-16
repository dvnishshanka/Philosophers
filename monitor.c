#include "philo.h"

// If the Philosopher is full, he is not dead
// Philosopher should not die while eating
static int has_phil_died(t_philo *philo)
{
    long    time_elapsed_after_last_meal;
    long    time_elapsed_from_start;
    long    last_meal_time;
    long    start_simulation_time;

    if (get_int(&philo->mtx_philo, &philo->is_full) == 1)
        return (0);
    start_simulation_time = get_long(&philo->table->mtx_table, &philo->table->start_simulation);
    time_elapsed_from_start = get_timestamp(MILLISEC) - start_simulation_time;
    if (time_elapsed_from_start <  get_long(&philo->table->mtx_table, &philo->table->time_to_die))
        return (0);
    last_meal_time = get_long(&philo->mtx_philo, &philo->last_meal_time);
    time_elapsed_after_last_meal = get_timestamp(MILLISEC) - last_meal_time;
    if (start_simulation_time != last_meal_time && time_elapsed_after_last_meal <= get_long(&philo->table->mtx_table, &philo->table->time_to_eat))
        return (0);
    if (time_elapsed_after_last_meal > get_long(&philo->table->mtx_table, &philo->table->time_to_die))
        return (1);
    return (0);
}

void    *monitor_philos(void *arg)
{
    int     i;
    t_table *table;

    table = (t_table *)arg;
    wait_till_threads_ready(table);
    while (simulation_finished(table) == 0)
    {
        i = -1;
        while (++i < get_int(&table->mtx_table, &table->nbr_philo) && simulation_finished(table) == 0)
        {
            if (has_phil_died(&table->philos[i]) == 1)
            {
                set_int(&table->mtx_table, &table->is_end_simulation, 1);
                write_state(DIED, table, &table->philos[i]);
            }
        }
        usleep(1000);
    }
    return (NULL);
}