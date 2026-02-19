/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:14:06 by hcissoko          #+#    #+#             */
/*   Updated: 2026/02/19 15:03:08 by hcissoko         ###   ########.fr       */
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
	pthread_mutex_t	fork1;
	pthread_mutex_t	fork2;

	philo = (t_philosopher *)arg;
	// printf("%ld %d has taken a fork", get_current_time(), philo->id);
	fork1 = philo->data->forks[philo->id - 1];
	fork1 = philo->data->forks[philo->id % philo->nb_philo];
}