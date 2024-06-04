/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:57:13 by ybahij            #+#    #+#             */
/*   Updated: 2024/06/04 17:07:12 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat_(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->data->stop)
	{
		if (get_fork(philo) == -1)
			break ;
		print_("is sleeping", philo);
		ft_sleep(philo->data->t_sleep, philo->data);
	}
	return (0);
}


void	*monitor(void *args)
{
	t_philo	*philos;
	int		i;
	int		all_eat;

	philos = (t_philo *)args;
	while (!philos->data->stop)
	{
		i = -1;
		all_eat = 0;
		while (++i < philos->data->num_philos)
		{
			if (gettime() - (philos + i)->t_meal > philos->data->t_die)
			{
				print_("died", philos + i);
				philos->data->stop = 1;
				break ;
			}
			if (philos->data->num_eat != -1 && \
				(philos + i)->num_eat_count >= philos->data->num_eat)
				all_eat++;
		}
		if (all_eat == philos->data->num_philos)
			philos->data->stop = 1;
	}
	return (0);
}

int start_simulation(t_philo *philos)
{
	int i;

	i = -1;
	philos->data->t_start = gettime();
	while (++i < philos->data->num_philos)
	{
		(philos + i)->t_meal = gettime();
		if (pthread_create(&(philos + i)->pth_t, NULL, &eat_, philos + i))
			return (ft_error("Error: pthread_create", philos->data));
		pthread_detach((philos + i)->pth_t);
		usleep(40);
	}
	if (pthread_create(&philos->data->check_monitor, NULL, &monitor, philos))
		return (ft_error("Error: pthread_create", philos->data));
	pthread_join(philos->data->check_monitor, NULL);
	i = -1;
	while (++i < philos->data->num_forks)
		pthread_mutex_destroy(&philos->data->mutex_fork[i]);
	pthread_mutex_destroy(&philos->data->mutex_printf);
	pthread_mutex_destroy(&philos->data->mutex_meals);
	return (0);
}

int main(int ac, char **av)
{
    t_philo *philos;

    if (ac < 5 || ac > 6)
        return (ft_error("Error: Wrong arguments\n", NULL));
    else
	{
		if (init_philos(&philos, ac, av) == -1)
        	return (1);
		if (start_simulation(philos) == -1)
			return (1);
	}
    return (0);
}
