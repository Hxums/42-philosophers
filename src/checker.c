/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:20:06 by hcissoko          #+#    #+#             */
/*   Updated: 2026/03/04 15:57:05 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		if (!argv[i][0])
		{
			printf("argv[%i] is empty\n", i);
			exit(1);
		}
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]) || ft_atol(argv[i]) > INT_MAX ||
				ft_atol(argv[i]) <= 0)
			{
				printf("%s is not a valid parameter\n", argv[i]);
				exit(1);
			}
		}
	}
}

void	check_args_number(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("You can only use it with 4 arguments (+1 optional)\n\
Example : ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		exit (1);
	}
}
