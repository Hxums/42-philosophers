/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 01:48:14 by hcissoko          #+#    #+#             */
/*   Updated: 2026/02/19 13:58:07 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eating_times;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philosopher
{
	int		id;
	int		nb_philo;
	t_data	*data;
	long	eating_times;
	long	last_eating_time;
}	t_philosopher;

int			ft_isdigit(int c);
long		ft_atol(char *str);
suseconds_t	get_current_time(void);
void		*routine(void *arg);

#endif