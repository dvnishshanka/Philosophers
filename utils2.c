#include "philo.h"

// If the simulation_finished sleep is interrrupted.
// Every 1ms, it is checked whether the simulation is finished
void    sleep_with_interruption(long sleep_time, t_table *table)
{
    long    time_limit;

    time_limit = get_timestamp(MICROSEC) + (sleep_time * 1e3);
    while (simulation_finished(table) == 0 && get_timestamp(MICROSEC) < time_limit)
    {
        usleep(1000);
    }
}