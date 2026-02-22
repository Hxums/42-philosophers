/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:18:53 by hcissoko          #+#    #+#             */
/*   Updated: 2026/02/22 20:55:22 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) || ft_atol(argv[i]) > INT_MAX ||
				ft_atol(argv[i]) <= 0)
			{
				printf("%s is not a valid parameter\n", argv[i]);
				exit(1);
			}
			j++;
		}
		i++;
	}
	if (atol(argv[1]) == 0)
		exit(1);
}

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
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_data	gen_data(char **argv, pthread_mutex_t *forks)
{
	t_data	data;

	data.start_time = get_current_time();
	data.forks = forks;
	data.time_to_die = ft_atol(argv[2]);
	data.time_to_eat = ft_atol(argv[3]);
	data.time_to_sleep = ft_atol(argv[4]);
	data.must_eating_times = -1;
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
	i = 0;
	while (i < nb_philo)
	{
		list[i].id = i + 1;
		list[i].nb_philo = nb_philo;
		list[i].data = data;
		list[i].last_eating_time = data->start_time;
		list[i].eating_times = 0;
		pthread_mutex_init(&list[i].eat_lock, NULL);
		i++;
	}
	return (list);
}

int	main(int argc, char **argv)
{
	t_philosopher	*list;
	t_data			data;
	pthread_mutex_t	*forks;
	int				i;

	if (argv && argc != 5 && argc != 6)
	{
		printf("You can only use it with 4 arguments (+1 optional)\n \
		Example : ./philosopers number_of_philosophers time_to_die \
		time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return (1);
	}

	check_args(argc, argv);
	forks = gen_forks(ft_atol(argv[1]));
	if (!forks)
		return (printf("Malloc issue\n"), 1);
	data = gen_data(argv, forks);
	list = gen_philosophers(argv, &data);
	if (!list)
		return (printf("Malloc issue\n"), 1);
	i = -1;
	data.start_time = get_current_time();
	while (++i < ft_atol(argv[1]))
		pthread_create(&list[i].thread_id, NULL, routine, &list[i]);
	monitoring(list, ft_atol(argv[1]), &data);
	i = -1;
	while (++i < ft_atol(argv[1]))
		pthread_join(list[i].thread_id, NULL);
	// Nettoyage
	i = -1;
	while (++i < ft_atol(argv[1]))
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(&data.sim_lock);
	pthread_mutex_destroy(&data.write_lock);
	i = -1;
	while (++i < ft_atol(argv[1]))
		pthread_mutex_destroy(&list[i].eat_lock);
	free(forks);
	free(list);
	return (0);
}
