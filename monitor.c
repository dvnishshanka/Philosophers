#include "philo.h"

static int has_phil_died(t_philo *philo)
{
    long    time_elapsed;

    if (get_int(&philo->mtx_philo, &philo->is_full) == 1)
        return (0);
    time_elapsed = get_timestamp(MILLISEC) - get_long(&philo->mtx_philo, &philo->last_meal_time);
    if (time_elapsed > get_long(&philo->table->mtx_table, &philo->table->time_to_die))
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
        while (++i < get_int(&table->mtx_table, &table->nbr_philo))
        {
            if (has_phil_died(&table->philos[i]) == 1)
            {
                set_int(&table->mtx_table, &table->is_end_simulation, 1);
                write_state(DIED, table, &table->philos[i]);
                break;
            }
        }
        usleep(1000);
    }
    return (NULL);
}