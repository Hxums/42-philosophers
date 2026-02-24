/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:22:51 by hcissoko          #+#    #+#             */
/*   Updated: 2026/02/24 21:49:04 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


pthread_mutex_t	*gen_forks(int nb_philo)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

t_data	gen_data(char **argv, pthread_mutex_t *forks)
{
	t_data	data;

	data.forks = forks;
	data.time_to_die = ft_atol(argv[2]);
	data.time_to_eat = ft_atol(argv[3]);
	data.time_to_sleep = ft_atol(argv[4]);
	data.must_eating_times = -1;
	data.start_time = get_current_time();
	data.stop_sim = 0;
	if (argv[5])
		data.must_eating_times = ft_atol(argv[5]);
	pthread_mutex_init(&data.sim_lock, NULL);
	pthread_mutex_init(&data.write_lock, NULL);
	return (data);
}

t_philosopher	*gen_philosophers(char **argv, t_data *data)
{
	int				i;
	int				nb_philo;
	t_philosopher	*list;

	nb_philo = ft_atol(argv[1]);
	list = malloc(sizeof(t_philosopher) * (nb_philo));
	if (!list)
		return (NULL);
	i = -1;
	while (++i < nb_philo)
	{
		list[i].id = i + 1;
		list[i].nb_philo = nb_philo;
		list[i].data = data;
		list[i].last_eating_time = data->start_time;
		list[i].eating_times = 0;
		if (pthread_mutex_init(&list[i].eat_lock, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&list[i].eat_lock);
			free(list);
			return (NULL);
		}
	}
	return (list);
}
