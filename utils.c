/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:37:49 by hcissoko          #+#    #+#             */
/*   Updated: 2026/02/22 12:14:43 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(char *txt, t_philosopher *philo)
{
	int	stop;

	stop = get_stop(philo->data);
	pthread_mutex_lock(&philo->data->write_lock);
	if (!stop)
		printf("%ldms %d %s", get_time(philo->data), philo->id, txt);
	pthread_mutex_unlock(&philo->data->write_lock);
}

long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

long	get_time(t_data *data)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000
		+ current_time.tv_usec / 1000 - data->start_time);
}

int	get_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->sim_lock);
	stop = data->stop_sim;
	pthread_mutex_unlock(&data->sim_lock);
	return (stop);
}
