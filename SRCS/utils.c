/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgamiz-g <hgamiz-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:12:39 by hgamiz-g          #+#    #+#             */
/*   Updated: 2025/11/08 16:23:52 by hgamiz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
** Retrieves the tim with gettimeofday and returns it in the format specifed
** as a parameter: SECONDS, MILISECONDS, MICROSECONDS.
*/
long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf(RED"Error with gettimeofday\n"RST);
		exit(1);
	}
	if (time_code == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (time_code == MILISECONDS)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSECONDS)
		return ((tv.tv_sec * 1000000) + (tv.tv_usec));
	else
	{
		printf(RED"Error retrieving time"RST);
		exit(1);
	}
	return (-1);
}

/*
** Custom usleep with more precision
*/
void	precise_usleep(long usec, t_philosophers *philo)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime(MICROSECONDS);
	while (((gettime(MICROSECONDS) - start) < usec) && (!sim_finished(philo)))
	{
		elapsed = gettime(MICROSECONDS) - start;
		remaining = usec - elapsed;
		if (remaining > 1000)
			usleep(200);
		else
			while (((gettime(MICROSECONDS) - start) < usec)
				&& (!sim_finished(philo)))
				;
	}
}

/*
** Prints the number of meals eaten by each philosopher at the end of the
** simulation if a number of meals has been set and has been compiled
** with -DSHOW_MEALS=1 or 'make show_meaks'
*/
void	show_meals(t_philosophers *philo)
{
	int	i;

	i = -1;
	printf(M"-------Number of meals eaten 🍝-------\n"RST);
	while (++i < philo->n_philo)
	{
		printf("Philosopher %3d has eaten %3ld times ",
			philo->philos[i]->philo_num, philo->philos[i]->meals_eaten);
		if (philo->philos[i]->meals_eaten == philo->n_meals)
			printf("✅\n");
		else
			printf("🚨\n");
	}
}
