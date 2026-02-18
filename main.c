/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:18:53 by hcissoko          #+#    #+#             */
/*   Updated: 2026/02/18 17:11:12 by hcissoko         ###   ########.fr       */
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

t_philosopher	*gen_philosophers(char **argv)
{
	int				i;
	int				nb_philo;
	t_philosopher	*list;

	nb_philo = atol(argv[1]);
	list = malloc(sizeof(t_philosopher) * (nb_philo));
	if (!list)
	{
		printf("Error while creating list of philosophers (malloc issue)\n");
		exit(1);
	}
	i = 0;
	while (i < nb_philo)
	{
		list[i].id = i + 1;
		list[i].time_to_die = atol(argv[2]);
		list[i].time_to_eat = atol(argv[3]);
		list[i].time_to_sleep = atol(argv[4]);
		if (argv[5])
			list[i].eating_number_of_times = atol(argv[5]);
		else
			list[i].eating_number_of_times = 0;
		i++;
	}
	return (list);
}

int	main(int argc, char **argv)
{
	int				nb_philo;
	t_philosopher	*list;
	int				i;

	i = 0;
	nb_philo = atol(argv[1]);
	if (argv && argc != 4 && argc != 5)
	{
		printf("You can only use it with 4 arguments (+1 optional)\n \
		Example : ./philosopers number_of_philosophers time_to_die \
		time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	check_args(argc, argv);
	list = gen_philosophers(argv);
	while (i < nb_philo)
	{
		printf("Philosopher %d\ttime_to_die %d\ttime_to_eat %d\ttime_to_sleep\
	%d\teating_number_of_times %d\n",
			list[i].id, list[i].time_to_die, list[i].time_to_eat,
			list[i].time_to_sleep, list[i].eating_number_of_times);
			i++;
	}
}
