/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 19:16:24 by hcissoko          #+#    #+#             */
/*   Updated: 2026/02/25 09:05:48 by hcissoko         ###   ########.fr       */
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
		if (eating_times < data->must_eating_times)
			return (0);
		i++;
	}
	return (1);
}

void	kill_philo(t_data *data, t_philosopher philo)
{
	pthread_mutex_lock(&data->sim_lock);
	data->stop_sim = 1;
	pthread_mutex_unlock(&data->sim_lock);
	pthread_mutex_lock(&data->write_lock);
	printf("%ld %d died\n", get_time(data), philo.id);
	pthread_mutex_unlock(&data->write_lock);
}

void	swap_ids(t_philosopher *philos, int *ids, int i, int j)
{
	int	temp;

	if (philos[ids[i]].last_eating_time
		> philos[ids[j]].last_eating_time)
	{
		temp = ids[i];
		ids[i] = ids[j];
		ids[j] = temp;
	}
}

int	*sorted_ids(t_philosopher *philos, int nb_philo)
{
	int		i;
	int		j;
	int		*ids;

	ids = malloc(sizeof(int) * nb_philo);
	if (!ids)
		return (NULL);
	i = -1;
	while (++i < nb_philo)
		ids[i] = i;
	i = -1;
	while (++i < nb_philo)
	{
		j = i;
		while (++j < nb_philo)
		{
			pthread_mutex_lock(&philos[ids[i]].eat_lock);
			pthread_mutex_lock(&philos[ids[j]].eat_lock);
			swap_ids(philos, ids, i, j);
			pthread_mutex_unlock(&philos[ids[i]].eat_lock);
			pthread_mutex_unlock(&philos[ids[j]].eat_lock);
		}
	}
	return (ids);
}

void	monitoring(t_philosopher *philos, int nb_philo, t_data *data)
{
	int		i;
	long	last_eat;
	int		*ids;

	while (!all_done_eating(philos, nb_philo, data) && !get_stop(data))
	{
		i = -1;
		ids = sorted_ids(philos, nb_philo);
		if (!ids)
			return ;
		while (++i < nb_philo)
		{
			pthread_mutex_lock(&philos[ids[i]].eat_lock);
			last_eat = philos[ids[i]].last_eating_time;
			pthread_mutex_unlock(&philos[ids[i]].eat_lock);
			if (get_current_time() - last_eat > data->time_to_die)
			{
				kill_philo(data, philos[ids[i]]);
				return ;
			}
		}
		free(ids);
		usleep(100);
	}
}
