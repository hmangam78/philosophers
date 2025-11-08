/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgamiz-g <hgamiz-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:54:14 by hgamiz-g          #+#    #+#             */
/*   Updated: 2025/11/08 16:23:20 by hgamiz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
** Locks a mutex to set a boolean value, preventing it from being modified
** by another thread. Avoids race conditions.
*/
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

/*
** Locks a mutex to read a value preventing it from being modified by
** another thread
*/
bool	get_bool(pthread_mutex_t *mutex, bool *src)
{
	bool	result;

	pthread_mutex_lock(mutex);
	result = *src;
	pthread_mutex_unlock(mutex);
	return (result);
}

/*
** Locks a mutex to set a long value preventing it from being modifed
** by another thread
*/
void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

/*
** Retrieves a long value, locking it to avoid it from being accesed by
** another thread
*/
long	get_long(pthread_mutex_t *mutex, long *src)
{
	long	result;

	pthread_mutex_lock(mutex);
	result = *src;
	pthread_mutex_unlock(mutex);
	return (result);
}

/*
** Checks if the simulation has finished
*/
bool	sim_finished(t_philosophers *philo)
{
	return (get_bool(&philo->meal_mutex, &philo->finish));
}
