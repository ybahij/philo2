/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:59:58 by ybahij            #+#    #+#             */
/*   Updated: 2024/09/04 17:17:22 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, int i, t_data *data, pthread_mutex_t *forks)
{
	philo->index = i + 1;
	philo->num_eat_count = 0;
	philo->last_meal = gettime();
	philo->data = data;
	philo->mutex_eat = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->mutex_eat, NULL);
	if (i == 0)
	{
		philo->lf = forks + data->num_philos - 1;
		philo->rf = forks + i;
	}
	else
	{
		philo->lf = forks + i - 1;
		philo->rf = forks + i;
	}
}

int	init_philos(t_data *data, int argc, char **argv)
{
	t_philo	**tmp;
	int		i;

	if (init_data(data, argc, argv) == -1)
		return (-1);
	if (pthread_mutex_init(&data->mutex_printf, NULL))
		return (ft_error("Error: pthread_mutex_print", data));
	if (init_mutex_fork(data) == -1)
		return (-1);
	tmp = malloc(sizeof(t_philo *) * (data->num_philos + 1));
	if (!tmp)
		return (ft_error("Error: Failed to malloc philos", data));
	data->mutex_s_over = malloc(sizeof(pthread_mutex_t));
	i = -1;
	while (++i < data->num_philos)
	{
		tmp[i] = malloc(sizeof(t_philo));
		init_philo(tmp[i], i, data, data->mutex_fork);
	}
	tmp[i] = NULL;
	data->philos = tmp;
	return (0);
}

int	print_(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->data->mutex_s_over);
	if (philo->data->s_over)
	{
		pthread_mutex_unlock(philo->data->mutex_s_over);
		return (1);
	}
	pthread_mutex_unlock(philo->data->mutex_s_over);
	if (pthread_mutex_lock(&philo->data->mutex_printf))
		return (ft_error("Error: pthread_mutex_lock", philo->data));
	printf("%ld %d %s\n", gettime() - philo->data->t_start, philo->index, msg);
	if (pthread_mutex_unlock(&philo->data->mutex_printf))
		return (ft_error("Error: pthread_mutex_unlock", philo->data));
	return (0);
}

