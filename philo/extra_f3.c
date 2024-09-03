/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:59:58 by ybahij            #+#    #+#             */
/*   Updated: 2024/09/03 23:18:26 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, int i, t_data *data, pthread_mutex_t *forks)
{
	philo->index = i + 1;
	philo->num_eat_count = 0;
	philo->t_meal = 0;
	philo->data = data;
	if (philo->index % 2 == 0)
	{
		philo->lf = forks + ((i + 1) % data->num_philos);
		philo->rf = forks + i;
	}
	else
	{
		philo->lf = forks + i;
		philo->rf = forks + ((i + 1) % data->num_philos);
	}

}

int	init_philos(t_philo **philos, int argc, char **argv)
{
	t_data	*data;
	t_philo	*tmp;
	int		i;

	if (init_data(&data, argc, argv) == -1)
		return (-1);
	if (pthread_mutex_init(&data->mutex_printf, NULL))
		return (ft_error("Error: pthread_mutex_print", data));
	if (pthread_mutex_init(&data->mutex_stop, NULL))
		return (ft_error("Error: pthread_mutex_stop", data));
	if (pthread_mutex_init(&data->mutex_s, NULL))
		return (ft_error("Error: pthread_mutex_s", data));
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_mutex_init(data->mutex_check + i, NULL))
			return (ft_error("Error: pthread_mutex_check", data));
	}
	if (init_mutex_fork(data) == -1)
		return (-1);
	tmp = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	if (!tmp)
		return (ft_error("Error: Failed to malloc philos", data));
	i = -1;
	while (++i < data->num_philos)
		init_philo(tmp + i, i, data, data->mutex_fork);
	*philos = tmp;
	data->philos = tmp;
	return (0);
}

int	print_(char *msg, t_philo *philo)
{
	if (ft_stop(philo) == 1)
		return (1);
	if (pthread_mutex_lock(&philo->data->mutex_printf))
		return (ft_error("Error: pthread_mutex_lock", philo->data));
	printf("%ld %d %s\n", gettime() - philo->data->t_start, philo->index, msg);
	if (pthread_mutex_unlock(&philo->data->mutex_printf))
		return (ft_error("Error: pthread_mutex_unlock", philo->data));
	return (0);
}
int ft_stop(t_philo *philo)
{
	int res ;

	res = 0;
	pthread_mutex_lock(&philo->data->mutex_s);
	if(philo->data->stop == 1)
		res = 1;
	pthread_mutex_unlock(&philo->data->mutex_s);
	return (res);
}

void	put_stop(t_data *data)
{
	pthread_mutex_lock(&data->mutex_s);
	data->stop = 1;
	pthread_mutex_unlock(&data->mutex_s);
}

int	eat_time(t_philo *philo)
{
    if (pthread_mutex_lock(&philo->data->mutex_check[philo->index - 1]))
        return (ft_error("Error: pthread_mutex_lock", philo->data));
    philo->t_meal = gettime();
    if (pthread_mutex_unlock(&philo->data->mutex_check[philo->index - 1]))
        return (ft_error("Error: pthread_mutex_unlock", philo->data));
    return (0);
}

int	get_fork(t_philo *philo)
{
	if (ft_stop(philo))
		return (1);
	if (pthread_mutex_lock(philo->lf))
		return (ft_error("Error: pthread_mutex_lock", philo->data));
	if (print_("has taken a fork", philo))
	{
		pthread_mutex_unlock(philo->lf);
		return (1);
	}
	if (pthread_mutex_lock(philo->rf))
	{
		pthread_mutex_unlock(philo->lf);
		return (ft_error("Error: pthread_mutex_lock", philo->data));
	}
	if (print_("has taken a fork", philo))
	{
		pthread_mutex_unlock(philo->lf);
		return (pthread_mutex_unlock(philo->rf), 1);
	}
	if (eat_time(philo))
	{
		pthread_mutex_unlock(philo->lf);
		return (pthread_mutex_unlock(philo->rf), 1);
	}
	return (0);
}
