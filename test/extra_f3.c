/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:57:36 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/19 22:22:31 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf(char *msg, int id, t_data *data)
{
	if (data->end_simulation == 1)
		return ;
	pthread_mutex_lock(&data->w);
	printf(msg, gettime() - data->start_simulation, id + 1);
	pthread_mutex_unlock(&data->w);
}

void	get_forke(t_data *data, int id)
{
	if (data->end_simulation == 1)
		return ;
	pthread_mutex_lock(&data->fork[id]);
	ft_printf("%ld: philo n[%d] take the first fork\n", id, data);
	pthread_mutex_lock(&data->fork[(id + 1) % data->philo_nbr]);
	if (data->end_simulation == 1)
	{
		pthread_mutex_unlock(&data->fork[id]);
		pthread_mutex_unlock(&data->fork[(id + 1) % data->philo_nbr]);
		return ;
	}
	ft_printf("%ld: philo n[%d] take the scond fork\n", id, data);
	ft_printf("%ld: the philo n:[%d] is eating\n", id, data);
	pthread_mutex_lock(&data->m_eat);
	data->laste_meal[id] = gettime();
	pthread_mutex_unlock(&data->m_eat);
	ft_sleep(data->tm_eat, data);
	if (data->end_simulation == 1)
	{
		pthread_mutex_unlock(&data->fork[id]);
		pthread_mutex_unlock(&data->fork[(id + 1) % data->philo_nbr]);
		return ;
	}
	pthread_mutex_unlock(&data->fork[id]);
	pthread_mutex_unlock(&data->fork[(id + 1) % data->philo_nbr]);
}

int	if_is_digit(const char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

long	ft_atol(char *s, t_data *data)
{
	const char	*str;
	long		n;

	n = 0;
	str = valid_str(s, data);
	while (*str >= '0' && *str <= '9')
		n = (n * 10) + (*str++ - '0');
	if (n > INT_MAX)
		ft_error("the value is to big, INTMAX is the limit\n", data);
	return (n);
}
