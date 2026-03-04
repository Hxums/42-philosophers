/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 19:16:24 by hcissoko          #+#    #+#             */
/*   Updated: 2026/03/04 17:28:36 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_done_eating(t_philosopher *list, int nb_philo, t_data *data)
{
	int		i;
	long	eating_times;

	i = 0;
	if (data->must_eating_times == -1)
		return (0);
	while (i < nb_philo)
	{
		pthread_mutex_lock(&list[i].eat_lock);
		eating_times = list[i].eating_times;
		pthread_mutex_unlock(&list[i].eat_lock);
		if (eating_times < data->must_eating_times)
			return (0);
		i++;
	}
	return (1);
}

void	kill_philo(t_data *data, t_philosopher philo)
{
	pthread_mutex_lock(&data->write_lock);
	pthread_mutex_lock(&data->sim_lock);
	data->stop_sim = 1;
	pthread_mutex_unlock(&data->sim_lock);
	printf("%ld %d died\n", get_time(data), philo.id);
	pthread_mutex_unlock(&data->write_lock);
}

void	monitoring(t_philosopher *philos, int nb_philo, t_data *data)
{
	int		i;
	long	last_eat;

	while (!get_stop(data) && !all_done_eating(philos, nb_philo, data))
	{
		i = -1;
		while (++i < nb_philo)
		{
			pthread_mutex_lock(&philos[i].eat_lock);
			last_eat = philos[i].last_eating_time;
			pthread_mutex_unlock(&philos[i].eat_lock);
			if (get_current_time() - last_eat >= data->time_to_die)
			{
				kill_philo(data, philos[i]);
				return ;
			}
		}
		usleep(1000);
	}
}
