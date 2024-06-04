/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:58:55 by ybahij            #+#    #+#             */
/*   Updated: 2024/06/04 06:02:26 by ybahij           ###   ########.fr       */
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
    int INT_MAX;

    INT_MAX = 2147483647;
	n = 0;
	str = valid_str(s, data);
	if (!str)
		return (-2);
	while (*str >= '0' && *str <= '9')
		n = (n * 10) + (*str++ - '0');
	if (n > INT_MAX)
		return (ft_error("Error: the value is to big, INTMAX is the limit\n", data),
			-2);
	return (n);
}

int	init_data(t_data **data, int argc, char **argv)
{
	t_data	*tmp;

	tmp = malloc(sizeof(t_data));
	if (!tmp)
		return (ft_error("Error: Failed to malloc data", tmp));
	tmp->num_philos = ft_atol(argv[1], tmp);
	tmp->num_forks = tmp->num_philos;
	tmp->t_die = ft_atol(argv[2], tmp);
	tmp->t_eat = ft_atol(argv[3], tmp);
	tmp->t_sleep = ft_atol(argv[4], tmp);
	if (tmp->num_philos < 1 || tmp->num_philos > 200 || tmp->t_die == -2 || \
		tmp->t_eat == -2 || tmp->t_sleep == -2)
		return (-1);
	tmp->num_eat = -1;
	if (argc == 6)
	{
		tmp->num_eat = ft_atol(argv[5], tmp);
		if (tmp->num_eat == -2)
			return (-1);
	}
	tmp->stop = 0;
	tmp->c_meals = 0;
	*data = tmp;
	return (0);
}

int	init_mutex_fork(t_data *data)
{
	int				i;

	data->mutex_fork = malloc(sizeof(pthread_mutex_t) \
					* data->num_forks);
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
