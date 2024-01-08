#include "philo.h"

long error_exit(const char *error_msg)
{
	printf("%s\n", error_msg);
	return (ERROR_CODE);
}

void	free_all(t_table *table)
{
	free(table->forks);
	free(table->philos);
}
