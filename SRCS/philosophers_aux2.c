/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_aux2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgamiz-g <hgamiz-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 07:45:40 by hgamiz-g          #+#    #+#             */
/*   Updated: 2025/11/08 16:23:28 by hgamiz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/* Initializes the fields in an individual philosophers and its mutexes */
static void	init_philosopher(t_philo *philos, int i)
{
	philos->philo_num = (i + 1);
	philos->last_meal = 0;
	philos->meals_eaten = 0;
	philos->finished = false;
	philos->r_fork = malloc(sizeof(pthread_mutex_t));
	if (!philos->r_fork)
		clean_exit(philos->global);
	philos->philo_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philos->philo_mutex)
		clean_exit(philos->global);
	pthread_mutex_init(philos->r_fork, NULL);
	pthread_mutex_init(philos->philo_mutex, NULL);
}

/*
** Allocates memory for the individual philosophers and calls the 
** initializer function
*/
static void	init_individual_philosophers(t_philosophers *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n_philo)
	{
		philo->philos[i] = malloc(sizeof(t_philo));
		if (!philo->philos[i])
			clean_exit(philo);
		philo->philos[i]->global = philo;
		init_philosopher(philo->philos[i], i);
	}
}

/* 
 * Initializes the t_philosophers struct, its mutexes and calls the 
 * function that initializes the individual philosophers.
*/
static void	init_philo_struct(t_philosophers *philo, char **argv)
{
	philo->n_philo = ft_atol(argv[1]);
	philo->t_die = ft_atol(argv[2]) * 1000;
	philo->t_eat = ft_atol(argv[3]) * 1000;
	philo->t_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5] != NULL)
		philo->n_meals = ft_atol(argv[5]);
	else
		philo->n_meals = -1;
	philo->finish = false;
	philo->all_ready = false;
	philo->philos_working = 0;
	pthread_mutex_init(&philo->meal_mutex, NULL);
	pthread_mutex_init(&philo->print_mutex, NULL);
	philo->philos = malloc(sizeof(t_philo *) * philo->n_philo);
	if (!philo->philos)
		clean_exit(philo);
	init_individual_philosophers(philo);
}

/* Assigns the left forks for each philosopher */
static void	link_forks(t_philosophers *philo)
{
	int	i;
	int	philo_n;

	philo_n = philo->n_philo;
	i = 0;
	while (i < philo_n)
	{
		if (i == 0)
			philo->philos[0]->l_fork = philo->philos[philo_n - 1]->r_fork;
		else
			philo->philos[i]->l_fork = philo->philos[i - 1]->r_fork;
		i++;
	}
}

/* Creates the t_philosophers struct and calls the init function */
t_philosophers	*init_philosophers(char **argv)
{
	t_philosophers	*philo;

	philo = malloc(sizeof(t_philosophers));
	if (!philo)
	{
		printf(RED"Problem allocating resources"RST);
		return (NULL);
	}
	init_philo_struct(philo, argv);
	link_forks(philo);
	return (philo);
}
