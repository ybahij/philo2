/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:57:13 by ybahij            #+#    #+#             */
/*   Updated: 2024/06/11 16:40:19 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat_(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->data->mutex_meals);
	philo->t_meal = gettime();
	pthread_mutex_unlock(&philo->data->mutex_meals);
	while (1)
	{
		if (philo->data->num_eat != -1 &&  philo->num_eat_count >= philo->data->num_eat)
			break;
		if (get_fork(philo) == -1)
			break ;
		if (print_("is sleeping", philo))
		{
			//philo->data->stop = 1;
			break ;
		}
		ft_sleep(philo->data->t_sleep, philo->data);
		// if (philo->data->num_eat != -1 &&  philo->num_eat_count >= philo->data->num_eat)
		// 	break;
	}
	return (0);
}

int	t_daeth(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_meals);
	if (gettime() - philo->t_meal > philo->data->t_die)
	{
		print_("died", philo);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->s);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_meals);
	return (0);
}

int	cheak_(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->mutex_check))
		return (ft_error("Error: pthread_mutex_lock", philo->data), 1);
	if (philo->data->s_cheak != 1)
	{
		pthread_mutex_unlock(&philo->data->mutex_check);
		return (1);
	}
	if (pthread_mutex_unlock(&philo->data->mutex_check))
		return (ft_error("Error: pthread_mutex_unlock", philo->data), 1);
	return (0);
}

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
	//int		all_eat;

	philos = (t_philo *)args;
	while (ft_stop(philos) == 0)
	{
		i = -1;
		while (++i < philos->data->num_philos)
		{
			if (philos->data->num_eat != -1 &&  philos->num_eat_count >= philos->data->num_eat)
				break;
			if (cheak_(philos))
				break ;
			pthread_mutex_lock(&philos->data->mutex_meals);
			if (gettime() - philos->t_meal > philos->data->t_die)
			{
				print_("died", philos);
				philos->data->stop = 1;
				pthread_mutex_unlock(&philos->data->mutex_meals);
				break;
			}
			pthread_mutex_unlock(&philos->data->mutex_meals);
			
		}
		if (all_(philos->data))
			break ;
	}
	return (0);
}

void	philo_exit(t_philo *philos)
{
	// int	i;

	// i = -1;
	// while (++i < philos->data->num_philos)
	// {
	// 	pthread_mutex_destroy(philos->data->mutex_fork + i);
	// }
	// pthread_mutex_destroy(&philos->data->mutex_stop);
	// pthread_mutex_destroy(&philos->data->mutex_meals);
	// pthread_mutex_destroy(&philos->data->mutex_printf);
	// pthread_mutex_destroy(&philos->data->s);
	free(philos->data->mutex_fork);
	free(philos->data);
	free(philos);
}

void	put_cheak(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->mutex_check);
	philo->data->s_cheak = i;
	pthread_mutex_unlock(&philo->data->mutex_check);
}

int	start_simulation(t_philo *philos)
{
	int	i;

	i = -1;
	put_cheak(philos, 0);
	if (pthread_create(&philos->data->check_monitor, NULL, &monitor, philos))
		return (ft_error("Error: pthread_create", philos->data));
	philos->data->t_start = gettime();
	while (++i < philos->data->num_philos)
	{
		if (pthread_create(&(philos + i)->pth_t, NULL, &eat_, philos + i))
			return (ft_error("Error: pthread_create", philos->data));
		//pthread_detach((philos + i)->pth_t);
		usleep(100);
	}
	put_cheak(philos, 1);
	i = -1;
	while (++i < philos->data->num_philos)
		pthread_join((philos + i)->pth_t, NULL);
	pthread_join(philos->data->check_monitor, NULL);
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
