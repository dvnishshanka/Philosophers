#include "philo.h"

long error_exit(const char *error_msg)
{
	printf("%s\n", error_msg);
	return (ERROR_CODE);
}

// If successful, all mutex functions will return zero.
static long	handle_mutex_errors(int state)
{
	if (state == 0)
		return (0);
	else
		return error_exit("Mutex Error Occured.");
}

long	safe_mutex_handle(t_mtx *mutex, t_mtx_state mtx_state)
{
	if (MTX_LOCK == mtx_state)
		return handle_mutex_errors(pthread_mutex_lock(mutex));
	else if (MTX_UNLOCK == mtx_state)
		return handle_mutex_errors(pthread_mutex_unlock(mutex));
	else if (MTX_INIT == mtx_state)
		return handle_mutex_errors(pthread_mutex_init(mutex, NULL));
	else if (MTX_DESTROY == mtx_state)
		return handle_mutex_errors(pthread_mutex_destroy(mutex));
	else
		return error_exit("Wrong Mutex State.\nUse 'MTX_LOCK' 'MTX_UNLOCK' 'MTX_INIT' 'MTX_DESTROY'.");
}