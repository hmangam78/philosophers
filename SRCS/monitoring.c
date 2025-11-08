/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgamiz-g <hgamiz-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 23:19:34 by hgamiz-g          #+#    #+#             */
/*   Updated: 2025/11/08 16:23:22 by hgamiz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
** 1st checks if the philosopher has finished eating its number of meals,
** if so returns false as he didn't die
** 2nd checks if he had starved, if so, returns true.
*/
static bool	dead(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(philo->philo_mutex, &philo->finished))
		return (false);
	elapsed = gettime(MILISECONDS) - get_long(philo->philo_mutex,
			&philo->last_meal);
	t_to_die = (philo->global->t_die) / 1000;
	if (elapsed > t_to_die)
		return (true);
	else
		return (false);
}

/*
** If all the philosophers are running, it simply observes
** If the simulation has finished, it checks if a philosopher died and
** printf its status
*/
void	*monitor_meal(void *data)
{
	int				i;
	t_philosophers	*ph;

	ph = (t_philosophers *)data;
	while (!ph_working(&ph->meal_mutex, &ph->philos_working, ph->n_philo))
		;
	while (!sim_finished(ph))
	{
		i = -1;
		while ((++i < ph->n_philo) && (!sim_finished(ph)))
		{
			if (dead(ph->philos[i]))
			{
				set_bool(&ph->meal_mutex, &ph->finish, true);
				print_status(DEAD, ph->philos[i]);
			}
		}
	}
	return (NULL);
}
