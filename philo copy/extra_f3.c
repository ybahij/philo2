/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:59:58 by ybahij            #+#    #+#             */
/*   Updated: 2024/06/04 16:40:42 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	init_philo(t_philo *philo, int i, \
						t_data *data, pthread_mutex_t *forks)
{
	philo->index = i + 1;
	philo->num_eat_count = 0;
	philo->t_meal = 0;
	philo->data = data;
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

int	init_philos(t_philo **philos, int argc, char **argv)
{
	t_data	*data;
	t_philo	*tmp;
	int		i;

	if (init_data(&data, argc, argv) == -1)
		return (-1);
	if (pthread_mutex_init(&data->mutex_printf, NULL))
		return (ft_error("Error: pthread_mutex_print", data));
	if (pthread_mutex_init(&data->mutex_meals, NULL))
		return (ft_error("Error: pthread_mutex_meals", data));
	if (init_mutex_fork(data) == -1)
		return (-1);
	tmp = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	if (!tmp)
		return (ft_error("Error: Failed to malloc philos", data));
	i = -1;
	while (++i < data->num_philos)
		init_philo(tmp + i, i, data, data->mutex_fork);
	*philos = tmp;
	return (0);
}

int 	print_(char *msg, t_philo *philo)
{
	if (philo->data->stop)
		return (1);
	if (pthread_mutex_lock(&philo->data->mutex_printf))
		return (ft_error("Error: pthread_mutex_lock", philo->data));
	printf("%ld %d %s\n", gettime() - philo->data->t_start, philo->index, msg);
	if (pthread_mutex_unlock(&philo->data->mutex_printf))
		return (ft_error("Error: pthread_mutex_unlock", philo->data));
	return (0);
}

int	get_fork(t_philo *philo)
{
	if (philo->data->stop)
		return (0);
	if (pthread_mutex_lock(philo->lf))
		return (ft_error("Error: pthread_mutex_lock", philo->data));
	if (print_("has taken a fork", philo) == -1)
		return (-1);
	if (pthread_mutex_lock(philo->rf))
		return (ft_error("Error: pthread_mutex_lock", philo->data));
	if (print_("has taken a fork", philo) == -1)
		return (-1);
	
	philo->num_eat_count++;
	if (print_("is eating", philo) == -1)
		return (-1);
	ft_sleep(philo->data->t_eat, philo->data);
	philo->t_meal = gettime();
	if (pthread_mutex_unlock(philo->lf))
		return (ft_error("Error: pthread_mutex_unlock", philo->data));
	if (pthread_mutex_unlock(philo->rf))
		return (ft_error("Error: pthread_mutex_unlock", philo->data));
	return (0);
}
