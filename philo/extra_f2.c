/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:58:55 by ybahij            #+#    #+#             */
/*   Updated: 2024/09/04 16:57:09 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

char	*valid_str(char *str, t_data *data)
{
	while (ft_space(*str))
		return (ft_error("Error: only numeric values are allowed", data), NULL);
	if (*str == '-')
		return (ft_error("Error: only positive values", data), NULL);
	else if (*str == '+')
		++str;
	while (*str == '0')
		++str;
	if (*str && !if_is_digit(str))
		return (ft_error("Error: only numeric values are allowed", data), NULL);
	if (*str && ft_strlen(str) > 11)
		return (ft_error("Error: gerter than INTMAX", data), NULL);
	return (str);
}

long	ft_atol(char *s, t_data *data)
{
	const char	*str;
	long		n;
	int			int_max;

	int_max = 2147483647;
	n = 0;
	str = valid_str(s, data);
	if (!str)
		return (-2);
	while (*str >= '0' && *str <= '9')
		n = (n * 10) + (*str++ - '0');
	if (n > int_max)
		return (ft_error("Error: the value is to big, INTMAX is the limit\n",
				data), -2);
	return (n);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atol(argv[1], data);
	data->num_forks = data->num_philos;
	data->t_die = ft_atol(argv[2], data);
	data->t_eat = ft_atol(argv[3], data);
	data->t_sleep = ft_atol(argv[4], data);
	if (data->num_philos < 1 || data->num_philos > 200 || data->t_die == -2
		|| data->t_eat == -2 || data->t_sleep == -2)
		return (-1);
	data->num_eat = -1;
	if (argc == 6)
	{
		data->num_eat = ft_atol(argv[5], data);
		if (data->num_eat == -2)
			return (-1);
	}
	data->stop = 0;
	data->c_meals = 0;
	data->s_over = 0;
	pthread_mutex_init(&data->mutex_s_over, NULL);
	return (0);
}

int	init_mutex_fork(t_data *data)
{
	int	i;

	data->mutex_fork = malloc(sizeof(pthread_mutex_t) * data->num_forks);
	if (!data->mutex_fork)
		return (ft_error("Error: Failed to malloc forks", data));
	i = -1;
	while (++i < data->num_forks)
	{
		if (pthread_mutex_init(data->mutex_fork + i, NULL))
			return (ft_error("Error: pthread_mutex_fork", data));
	}
	return (0);
}
