/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 08:18:53 by hcissoko          #+#    #+#             */
/*   Updated: 2026/02/18 15:29:29 by hcissoko         ###   ########.fr       */
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
				exit(0);
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argv && argc != 4 && argc != 5)
	{
		printf("You can only use it with 4 arguments (+1 optional)\n \
		Example : ./philosopers number_of_philosophers time_to_die \
		time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	check_args(argc, argv);
}
