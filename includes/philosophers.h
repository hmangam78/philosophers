/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgamiz-g <hgamiz-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:52:02 by hgamiz-g          #+#    #+#             */
/*   Updated: 2025/07/20 21:24:23 by hgamiz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

/*
** Colour scheme for output
*/

# define RST	"\033[0m"		/* RST */
# define RED	"\033[1;31m"	/* Bold R */
# define G		"\033[1;32m"	/* Bold green */
# define W		"\033[1;37m"	/* Bold white */
# define Y		"\033[1;33m"	/* Bold yellow */
# define B		"\033[1;34m"	/* Bold blue */
# define M		"\033[1;35m"	/* Bold magenta */

/*
**	Flag for showing a summary of the meals eaten by the philosophers at exit
** run: make show_meals
*/
# ifndef SHOW_MEALS
#  define SHOW_MEALS false
# endif

typedef struct s_philosophers	t_philosophers;

typedef enum time_code
{
	SECONDS,
	MILISECONDS,
	MICROSECONDS,
}	t_time_code;

typedef enum philo_status
{
	EATING,
	THINKING,
	SLEEPING,
	TAKE_OWN_FORK,
	TAKE_OTHER_FORK,
	DEAD,
}	t_philo_status;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*philo_mutex;
	t_philosophers	*global;
	long			meals_eaten;
	long			last_meal;
	int				philo_num;
	bool			finished;
}	t_philo;

struct s_philosophers
{
	t_philo			**philos;
	pthread_t		monitor;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	print_mutex;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			n_meals;
	long			init_time;
	long			philos_working;
	int				n_philo;
	bool			finish;
	bool			all_ready;
};

/***********************error_checks.c******************************/
int				check_philo_data(t_philosophers *philo);
int				clean_exit(t_philosophers *philo);
int				check_parameters(int args, char **argv);
int				check_word(char *str);
int				arg_error(void);

/*********************philosophers_aux.c****************************/
void			free_philo(t_philosophers *philo);
int				ft_isdigit(char c);
long			ft_atol(char *string);

/*********************philosophers_aux2.c****************************/
t_philosophers	*init_philosophers(char **argv);

/***************************get_set.c********************************/
void			set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool			get_bool(pthread_mutex_t *mutex, bool *src);
void			set_long(pthread_mutex_t *mutex, long *dest, long value);
long			get_long(pthread_mutex_t *mutex, long *src);
bool			sim_finished(t_philosophers *philo);

/***************************sync_utils.c*****************************/
void			threads_ready(t_philosophers *philo);
bool			ph_working(pthread_mutex_t *mutex, long *threads, long p_num);
void			increase_long(pthread_mutex_t *mutex, long *value);
void			un_sync(t_philo *philo);

/*******************************utils.c******************************/
long			gettime(t_time_code time_code);
void			precise_usleep(long usec, t_philosophers *philo);
void			show_meals(t_philosophers *philo);

/****************************simulation.c****************************/
void			init_sim(t_philosophers *philo);
void			think(t_philo *philo, bool pre_sim);

/****************************print_status.c**************************/
void			print_status(t_philo_status status, t_philo *philo);

/****************************monitoring.c****************************/
void			*monitor_meal(void *data);

#endif