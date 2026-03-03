/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:20:06 by hcissoko          #+#    #+#             */
/*   Updated: 2026/03/03 14:44:16 by hcissoko         ###   ########.fr       */
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

void	check_args_number(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("You can only use it with 4 arguments (+1 optional)\n\
Example : ./philosopers number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		exit (1);
	}
}
