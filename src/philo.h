/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 01:48:14 by hcissoko          #+#    #+#             */
/*   Updated: 2026/03/03 14:43:27 by hcissoko         ###   ########.fr       */
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
	int				simulation_stopped;
	int				stop_sim;
	long			start_time;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	sim_lock;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread_id;
	int				nb_philo;
	t_data			*data;
	long			eating_times;
	long			last_eating_time;
	pthread_mutex_t	eat_lock;
}	t_philosopher;

void			check_args(int argc, char **argv);
void			check_args_number(int argc);
pthread_mutex_t	*gen_forks(int nb_philo);
t_data			gen_data(char **argv, pthread_mutex_t *forks);
t_philosopher	*gen_philosophers(char **argv, t_data *data);
int				get_stop(t_data *data);
int				ft_isdigit(int c);
long			ft_atol(char *str);
void			ft_usleep(long time_in_ms, t_data *data);
long			get_current_time(void);
long			get_time(t_data *data);
void			print_status(char *txt, t_philosopher *philo);
void			monitoring(t_philosopher *list, int nb_philo, t_data *data);
void			*routine(void *arg);
void			clean(t_data data, t_philosopher *philos, int nb_philo);
void			kill_philo(t_data *data, t_philosopher philo);
void			choose_forks(t_philosopher *philo, pthread_mutex_t **fork1,
					pthread_mutex_t **fork2);
#endif	