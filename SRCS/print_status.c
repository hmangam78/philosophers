/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgamiz-g <hgamiz-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:43:01 by hgamiz-g          #+#    #+#             */
/*   Updated: 2025/11/08 16:23:43 by hgamiz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
** Locks its mutex to print a philo's status, avoiding printing overlaps
*/
void	print_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	if (philo->finished)
		return ;
	elapsed = gettime(MILISECONDS) - philo->global->init_time;
	pthread_mutex_lock(&philo->global->print_mutex);
	if (((status == TAKE_OWN_FORK) || (status == TAKE_OTHER_FORK))
		&& !sim_finished(philo->global))
		printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->philo_num);
	else if ((status == EATING) && !sim_finished(philo->global))
		printf(M"%-6ld %d is eating\n"RST, elapsed, philo->philo_num);
	else if ((status == SLEEPING) && !sim_finished(philo->global))
		printf(W"%-6ld"RST" %d is sleeping\n", elapsed, philo->philo_num);
	else if ((status == THINKING) && !sim_finished(philo->global))
		printf(W"%-6ld"RST" %d is thinking\n", elapsed, philo->philo_num);
	else if (status == DEAD)
		printf(RED"%-6ld %d died\n"RST, elapsed, philo->philo_num);
	pthread_mutex_unlock(&philo->global->print_mutex);
}
