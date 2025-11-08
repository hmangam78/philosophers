/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgamiz-g <hgamiz-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:14:59 by hgamiz-g          #+#    #+#             */
/*   Updated: 2025/11/08 16:23:25 by hgamiz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
** Destroys the mutexes and frees all the allocated memory
*/
void	free_philo(t_philosophers *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n_philo)
	{
		if (philo->philos[i])
		{
			if (philo->philos[i]->r_fork)
			{
				pthread_mutex_destroy(philo->philos[i]->r_fork);
				free(philo->philos[i]->r_fork);
			}
			if (philo->philos[i]->philo_mutex)
			{
				pthread_mutex_destroy(philo->philos[i]->philo_mutex);
				free(philo->philos[i]->philo_mutex);
			}
			free(philo->philos[i]);
			philo->philos[i] = NULL;
		}
	}
	free(philo->philos);
	philo->philos = NULL;
	free(philo);
	philo = NULL;
}

int	ft_isdigit(char c)
{
	if ((c < '0') || (c > '9'))
		return (0);
	else
		return (1);
}

/* Returns a long from a string of digits */
long	ft_atol(char *string)
{
	long	num;
	int		signo;

	num = 0;
	signo = 1;
	while ((((*string >= 9) && (*string <= 13)) || (*string == ' ')) && *string)
		string++;
	if ((*string == '-') || (*string == '+'))
	{
		if (*string == '-')
			signo = -signo;
		string++;
	}
	while ((*string >= '0') && (*string <= '9'))
	{
		num = (10 * num) + (*string - '0');
		string++;
	}
	num = signo * num;
	return (num);
}
