/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:57:42 by hcissoko          #+#    #+#             */
/*   Updated: 2026/03/01 12:52:12 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long time_in_ms, t_data *data)
{
	long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time_in_ms)
	{
		if (get_stop(data))
			break ;
		usleep(100);
	}
}

void	choose_forks(t_philosopher *philo, pthread_mutex_t **fork1,
		pthread_mutex_t **fork2)
{
	if (philo->id % 2 == 0)
	{
		*fork1 = &philo->data->forks[philo->id - 1];
		*fork2 = &philo->data->forks[philo->id % philo->nb_philo];
	}
	else
	{
		*fork1 = &philo->data->forks[philo->id % philo->nb_philo];
		*fork2 = &philo->data->forks[philo->id - 1];
	}
}
