#include "philo.h"

int main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if ((parse_input(&table, argv)) == ERROR_CODE)
			return (1);
		if (data_init(&table) == ERROR_CODE)
			return (1);
		printf ("%ld", table.time_to_die);
	}

	else
	{
		error_exit("Wrong input.\nCorrect format: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return (1);
	}
return (0);
}