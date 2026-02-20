/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:14:06 by hcissoko          #+#    #+#             */
/*   Updated: 2026/02/19 23:37:36 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_usec);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	philo = (t_philosopher *)arg;
	fork1 = &philo->data->forks[philo->id - 1];
	fork2 = &philo->data->forks[philo->id % philo->nb_philo];
	while (1)
	{
		pthread_mutex_lock(fork1);
		pthread_mutex_lock(fork2);
		printf("%ld %d has taken forks\n", get_current_time(), philo->id);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(fork1);
		pthread_mutex_unlock(fork2);
		printf("%ld %d he's sleeping\n", get_current_time(), philo->id);
		usleep(philo->data->time_to_sleep * 1000);
	}
}
