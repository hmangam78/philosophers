/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgamiz-g <hgamiz-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:09:26 by hgamiz-g          #+#    #+#             */
/*   Updated: 2025/11/08 16:23:14 by hgamiz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
** Checks if the parameters are within the simulation limits and displays
** the correspondent error messages.
*/
int	check_philo_data(t_philosophers *philo)
{
	if ((philo->n_philo == 0) || (philo->n_philo > 200))
	{
		printf(RED"Error.\n"RST);
		printf("The number of philosophers must be between 0 and 200\n");
		return (1);
	}
	else if ((philo->t_die <= 60000) || (philo->t_die > ((long)INT_MAX * 1000))
		|| (philo->t_eat <= 60000) || (philo->t_eat > ((long)INT_MAX * 1000))
		|| (philo->t_sleep <= 60000)
		|| (philo->t_sleep > ((long)INT_MAX * 1000)))
	{
		printf(RED"Error.\n"RST);
		printf("Time to die, time to eat and time to sleep must be ");
		printf("greater than 60ms and less than INT_MAX.\n");
		return (1);
	}
	else if ((philo->n_meals == 0) || (philo->n_meals > INT_MAX))
	{
		printf(RED"Error.\n"RST);
		printf("Number of meals must be greater than 0 and ");
		printf("less than INT_MAX.\n");
		return (1);
	}
	else
		return (0);
}

/* Calls the function that frees the allocated memory */
int	clean_exit(t_philosophers *philo)
{
	free_philo(philo);
	return (0);
}

/* Iterates over the parameters and checks for valid input */
int	check_parameters(int args, char **argv)
{
	int	i;

	i = 1;
	while (i < args)
	{
		if (check_word(argv[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

/* Checks if all chars in a parameter are digits */
int	check_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

/* Displays an error message to tell the user the prompt right parameters */
int	arg_error(void)
{
	printf(RED"Incorrect input parameters.\n"RST);
	printf("Please enter: \'./philo <number_of_philosophers> <time_to_die> ");
	printf("<time_to_eat> <time_to_sleep> [optional_number_of_meals]'\n");
	return (1);
}
