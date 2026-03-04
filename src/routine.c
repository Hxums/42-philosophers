/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:14:06 by hcissoko          #+#    #+#             */
/*   Updated: 2026/03/04 09:10:44 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philosopher *philo)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	choose_forks(philo, &fork1, &fork2);
	pthread_mutex_lock(fork1);
	print_status("has taken a fork\n", philo);
	if (get_stop(philo->data))
	{
		pthread_mutex_unlock(fork1);
		return ;
	}
	pthread_mutex_lock(fork2);
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_eating_time = get_current_time();
	philo->eating_times++;
	pthread_mutex_unlock(&philo->eat_lock);
	print_status("has taken a fork\n", philo);
	print_status("is eating\n", philo);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(fork2);
	pthread_mutex_unlock(fork1);
}

void	sleeping(t_philosopher *philo)
{
	print_status("is sleeping\n", philo);
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	thinking(t_philosopher *philo)
{
	long	think_time;

	print_status("is thinking\n", philo);
	think_time = philo->data->time_to_die - philo->data->time_to_eat
		- philo->data->time_to_sleep;
	if (think_time > 0)
		ft_usleep(think_time / 2, philo->data);
}

void	solo_philo(t_philosopher *philo)
{
	print_status("has taken a fork\n", philo);
	ft_usleep(philo->data->time_to_die, philo->data);
	kill_philo(philo->data, *philo);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	int				eating_times;

	philo = (t_philosopher *)arg;
	if (philo->nb_philo == 1)
		return (solo_philo(philo), NULL);
	if (philo->id % 2 == 1)
		ft_usleep(philo->data->time_to_eat / 2, philo->data);
	while (!get_stop(philo->data))
	{
		eating(philo);
		pthread_mutex_lock(&philo->eat_lock);
		eating_times = philo->eating_times;
		pthread_mutex_unlock(&philo->eat_lock);
		if (eating_times == philo->data->must_eating_times)
			return (NULL);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
