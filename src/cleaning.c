/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:12:11 by hcissoko          #+#    #+#             */
/*   Updated: 2026/03/04 11:57:58 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_forks(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
}

void	clean(t_data *data, t_philosopher *philos, int nb_philo)
{
	int	i;

	if (data->forks)
		clean_forks(data->forks, nb_philo);
	pthread_mutex_destroy(&data->sim_lock);
	pthread_mutex_destroy(&data->write_lock);
	if (philos)
	{
		i = -1;
		while (++i < nb_philo)
			pthread_mutex_destroy(&philos[i].eat_lock);
		free(philos);
	}
}
