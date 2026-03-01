/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:18:53 by hcissoko          #+#    #+#             */
/*   Updated: 2026/03/01 09:53:09 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_sim(t_data *data, t_philosopher *philos, int nb_philo)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
	{
		if (pthread_create(&philos[i].thread_id, NULL, routine,
				&philos[i]) != 0)
		{
			pthread_mutex_lock(&data->sim_lock);
			data->stop_sim = 1;
			pthread_mutex_unlock(&data->sim_lock);
			printf("Error: Failed to create thread %d\n", i);
			break ;
		}
	}
	if (nb_philo > 1)
		monitoring(philos, nb_philo, data);
	i = -1;
	while (++i < nb_philo)
		pthread_join(philos[i].thread_id, NULL);
}

int	main(int argc, char **argv)
{
	t_philosopher	*philos;
	t_data			data;
	pthread_mutex_t	*forks;
	int				nb_philo;
	int				i;

	nb_philo = ft_atol(argv[1]);
	check_args_number(argc, argv);
	check_args(argc, argv);
	forks = gen_forks(nb_philo);
	if (!forks)
		return (printf("Malloc issue\n"), 1);
	data = gen_data(argv, forks);
	philos = gen_philosophers(argv, &data);
	if (!philos)
		return (clean(data, NULL, nb_philo), printf("Malloc issue\n"), 1);
	data.start_time = get_current_time();
	i = -1;
	while (++i < nb_philo)
		philos[i].last_eating_time = data.start_time;
	launch_sim(&data, philos, nb_philo);
	clean(data, philos, nb_philo);
}
