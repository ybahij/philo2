/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:57:13 by ybahij            #+#    #+#             */
/*   Updated: 2024/09/03 23:18:02 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long time)
{
	long	start;

	start = gettime();
	while (gettime() - start < time)
		usleep(500);
}

void	*eat_(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		if (get_fork(philo))
			return (0);
		if (print_("is eating", philo))
			return (0);
		ft_usleep(philo->data->t_eat * 1000);
		if (print_("is sleeping", philo))
			return (0);
		ft_usleep(philo->data->t_sleep * 1000);
		if (print_("is thinking", philo))
			return (0);
	}
	return (0);
}

int	t_daeth(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_check[philo->index - 1]);
	if (gettime() - philo->t_meal > philo->data->t_die)
	{
		print_("died", philo);
		put_stop(philo->data);
		pthread_mutex_unlock(&philo->data->mutex_check[philo->index - 1]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_check[philo->index - 1]);
	return (0);
}

// int	cheak_(t_philo *philo)
// {
// 	if (pthread_mutex_lock(philo->data->mutex_check[philo->index - 1]))
// 		return (ft_error("Error: pthread_mutex_lock", philo->data), 1);
// 	if (philo->data->s_cheak != 1)
// 	{
// 		pthread_mutex_unlock(&philo->data->mutex_check);
// 		return (1);
// 	}
// 	if (pthread_mutex_unlock(&philo->data->mutex_check))
// 		return (ft_error("Error: pthread_mutex_unlock", philo->data), 1);
// 	return (0);
// }

int	all_(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (data->num_eat != -1 && data->philos[i].num_eat_count < data->num_eat)
			return (1);
	}
	return (0);
}

void	*monitor(void *args)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)args;
	while (1)
	{
		i = -1;
		while (++i < philos->data->num_philos)
		{
			if (t_daeth(&philos[i]))
				return (0);
			// if (cheak_(&philos[i]))
			// 	return (0);
			if (all_(philos[i].data))
				return (0);
		}
	}
	return (0);
}

void	philo_exit(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->data->num_philos)
	{
		pthread_mutex_destroy(philos->data->mutex_fork + i);
		pthread_mutex_destroy(philos->data->mutex_check + i);
	}
	pthread_mutex_destroy(&philos->data->mutex_stop);
	pthread_mutex_destroy(&philos->data->mutex_printf);
	free(philos->data->mutex_fork);
	free(philos->data->mutex_check);
	free(philos->data);
	free(philos);
}

int	start_simulation(t_philo *philos)
{
	int	i;

	i = -1;
	philos->data->t_start = gettime();
	while (++i < philos->data->num_philos)
	{
		if (pthread_create(&philos[i].pth_t, NULL, eat_, &philos[i]))
			return (ft_error("Error: pthread_create", philos[i].data));
	}
	monitor(philos);
	i = -1;
	while (++i < philos->data->num_philos)
	{
		if (pthread_join(philos[i].pth_t, NULL))
			return (ft_error("Error: pthread_join", philos[i].data));
	}
	philo_exit(philos);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philos;

	if (ac < 5 || ac > 6)
		return (ft_error("Error: ./philo [n_p] [t_d] [t_e] [t_s]", NULL));
	else
	{
		if (init_philos(&philos, ac, av) == -1)
			return (1);
		if (start_simulation(philos) == -1)
			return (1);
	}
	return (0);
}
