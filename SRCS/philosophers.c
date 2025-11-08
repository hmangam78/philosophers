/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgamiz-g <hgamiz-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:51:51 by hgamiz-g          #+#    #+#             */
/*   Updated: 2025/11/08 16:23:40 by hgamiz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int args, char **argv)
{
	t_philosophers	*philo;

	if ((args != 5) && (args != 6))
		return (arg_error());
	if (check_parameters(args, argv) != 0)
		return (arg_error());
	philo = init_philosophers(argv);
	if (!philo)
		return (1);
	if (check_philo_data(philo))
		return (clean_exit(philo));
	init_sim(philo);
	if (SHOW_MEALS)
		show_meals(philo);
	free_philo(philo);
	return (0);
}
