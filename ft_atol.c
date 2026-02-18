/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:04:49 by hcissoko          #+#    #+#             */
/*   Updated: 2025/12/17 17:48:46 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c)
{
	return (
		c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v'
	);
}

long	ft_atol(char *str)
{
	int		i;
	int		sign;
	long	total;

	i = 0;
	sign = 1;
	total = 0;
	while (str[i] && ft_isspace(str[i]))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' )
			sign *= -1;
		i++;
	}
	while (str[i] && '0' <= str[i] && str[i] <= '9')
	{
		total = (total * 10) + str[i] - 48;
		i++;
	}
	return (total * sign);
}
