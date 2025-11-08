/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgamiz-g <hgamiz-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:29:53 by hgamiz-g          #+#    #+#             */
/*   Updated: 2025/11/08 16:23:46 by hgamiz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
** Function for only one philosopher. Initializes the variables and prints
** its status message
*/
static void	*solo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	threads_ready(philo->global);
	set_long(philo->philo_mutex, &philo->last_meal, gettime(MILISECONDS));
	increase_long(&philo->global->meal_mutex, &philo->global->philos_working);
	print_status(TAKE_OWN_FORK, philo);
	while (!sim_finished(philo->global))
		usleep(150);
	return (NULL);
}

/*
** Eating routine
** If the philo is even, first locks its fork and second the left one.
** If the philo is odd, does the opposite.
** This prevents deadlocks.
** Updates its last_meal time
** Increases its meal count
** Sleeps for the meal time
** If there's a maximum number of meals and it has reached it's limit, sets
** its flag to TRUE
*/
static void	eat(t_philo *philo)
{
	if (philo->philo_num % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(TAKE_OWN_FORK, philo);
		print_status(THINKING, philo);
		pthread_mutex_lock(philo->l_fork);
		print_status(TAKE_OTHER_FORK, philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(TAKE_OTHER_FORK, philo);
		print_status(THINKING, philo);
		pthread_mutex_lock(philo->r_fork);
		print_status(TAKE_OWN_FORK, philo);
	}
	set_long(philo->philo_mutex, &philo->last_meal, gettime(MILISECONDS));
	philo->meals_eaten++;
	print_status(EATING, philo);
	precise_usleep(philo->global->t_eat, philo->global);
	if ((philo->global->n_meals > 0)
		&& (philo->meals_eaten == philo->global->n_meals))
		set_bool(philo->philo_mutex, &philo->finished, true);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

/*
** Thinking routine
** If the simulation has already started, prints the status
** If there's an even number of philosophers, it simply returns because 
** there's no starvation possibility
** In other case, stablishes a thinking time that prevents starvation
*/
void	think(t_philo *philo, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (pre_sim)
		print_status(THINKING, philo);
	if (philo->global->n_philo % 2 == 0)
		return ;
	t_eat = philo->global->t_eat;
	t_sleep = philo->global->t_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.9, philo->global);
}

/*
** Simulation starter for each philosopher. 
** 1st checks if all are ready to begin.
** 2nd initializes its last_meal to the starting time
** 3rd Increases the number of philos_working saying that it is itself ready
** 4th 
*/
static void	*meal_sim(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	threads_ready(philo->global);
	set_long(philo->philo_mutex, &philo->last_meal, gettime(MILISECONDS));
	increase_long(&philo->global->meal_mutex, &philo->global->philos_working);
	un_sync(philo);
	while (!sim_finished(philo->global))
	{
		if (philo->finished)
			break ;
		eat(philo);
		print_status(SLEEPING, philo);
		precise_usleep(philo->global->t_sleep, philo->global);
		think(philo, false);
	}
	return (NULL);
}

/*
** Creates the threads for each philosopher, the monitor and establishes
** the init time. Also checks for only one philosopher.
*/
void	init_sim(t_philosophers *philo)
{
	int	i;

	i = -1;
	if (philo->n_philo == 1)
		pthread_create(&philo->philos[0]->thread, NULL,
			solo, philo->philos[0]);
	else
		while (++i < philo->n_philo)
			pthread_create(&philo->philos[i]->thread, NULL, meal_sim,
				philo->philos[i]);
	pthread_create(&philo->monitor, NULL, monitor_meal, philo);
	philo->init_time = gettime(MILISECONDS);
	set_bool(&philo->meal_mutex, &philo->all_ready, true);
	i = -1;
	while (++i < philo->n_philo)
		pthread_join(philo->philos[i]->thread, NULL);
	set_bool(&philo->meal_mutex, &philo->finish, true);
	pthread_join(philo->monitor, NULL);
}
