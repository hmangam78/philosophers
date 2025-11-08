/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgamiz-g <hgamiz-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:07:33 by hgamiz-g          #+#    #+#             */
/*   Updated: 2025/11/08 16:23:49 by hgamiz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
** Prevents the simulation from starting until all philos are ready and their
** threads are properly initialized
*/
void	threads_ready(t_philosophers *philo)
{
	while (!get_bool(&philo->meal_mutex, &philo->all_ready))
		;
}

/*
** Checks if the number of philosophers running is the same as
** the total number of philosophers
*/
bool	ph_working(pthread_mutex_t *mutex, long *threads, long p_num)
{
	bool	result;

	result = false;
	pthread_mutex_lock(mutex);
	if (*threads == p_num)
		result = true;
	pthread_mutex_unlock(mutex);
	return (result);
}

/*
** Increases a long value, locking it with a mutex to prevent it from being
** accesed by another thread. Avoids race conditions.
*/
void	increase_long(pthread_mutex_t *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	*value += 1;
	pthread_mutex_unlock(mutex);
}

/*
** Delays the start depending if there are an even or odd number of
** philosophers to prevent starvation when running synchronously
*/
void	un_sync(t_philo *philo)
{
	if (philo->global->n_philo % 2 == 0)
	{
		if (philo->philo_num % 2 == 0)
			precise_usleep(philo->global->t_eat * 0.5, philo->global);
	}
	else
	{
		if (philo->philo_num % 2)
			think(philo, true);
	}
}
