/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:18:53 by hcissoko          #+#    #+#             */
/*   Updated: 2026/02/19 10:03:45 by hcissoko         ###   ########.fr       */
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
			if (!ft_isdigit(argv[i][j]) || ft_atol(argv[i]) > INT_MAX)
			{
				printf("%s is not a valid parameter\n", argv[i]);
				exit(1);
			}
			j++;
		}
		i++;
	}
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

	data.forks = forks;
	data.time_to_die = ft_atol(argv[2]);
	data.time_to_eat = ft_atol(argv[3]);
	data.time_to_sleep = ft_atol(argv[4]);
	data.must_eating_times = 0;
	if (argv[5])
		data.must_eating_times = ft_atol(argv[5]);
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
		list[i].last_eating_time = 0;
		list[i].eating_times = 0;
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

	i = 0;
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
		return (printf("Error while creating philosophers (malloc issue)\n"), 1);
	data = gen_data(argv, forks);
	list = gen_philosophers(argv, &data);
	if (!list)
		return (printf("Error while creating philosophers (malloc issue)\n"), 1);
}
