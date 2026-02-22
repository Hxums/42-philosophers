/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 22:57:42 by hcissoko          #+#    #+#             */
/*   Updated: 2026/02/22 12:01:52 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long time_in_ms, t_data *data)
{
	long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time_in_ms)
	{
		if (get_stop(data))
			break ;
		usleep(500);
	}
}
