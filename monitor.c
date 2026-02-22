/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 19:16:24 by hcissoko          #+#    #+#             */
/*   Updated: 2026/02/22 20:53:41 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_done_eating(t_philosopher *list, int nb_philo, t_data *data)
{
	int		i;
	int		eating_times;

	i = 0;
	if (data->must_eating_times == -1)
		return (0);
	while (i < nb_philo)
	{
		pthread_mutex_lock(&list[i].eat_lock);
		eating_times = list[i].eating_times;
		pthread_mutex_unlock(&list[i].eat_lock);
		if (eating_times >= data->must_eating_times)
			return (0);
		i++;
	}
	return (1);
}


void	monitoring(t_philosopher *list, int nb_philo, t_data *data)
{
	int		i;
	long	last_eat;

	while (!all_done_eating(list, nb_philo, data) && !get_stop(data))
	{
		i = -1;
		while (++i < nb_philo)
		{
			pthread_mutex_lock(&list[i].eat_lock);
			last_eat = list[i].last_eating_time;
			pthread_mutex_unlock(&list[i].eat_lock);
			if (get_current_time() - last_eat > data->time_to_die)
			{
				pthread_mutex_lock(&data->write_lock);
				pthread_mutex_lock(&data->sim_lock);
				printf("%ldms %d died\n", get_time(data), list[i].id);
				data->stop_sim = 1;
				pthread_mutex_unlock(&data->sim_lock);
				pthread_mutex_unlock(&data->write_lock);
				return ;
			}
		}
		usleep(500);
	}
}
