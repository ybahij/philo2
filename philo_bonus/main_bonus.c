/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:28:25 by ybahij            #+#    #+#             */
/*   Updated: 2024/06/09 20:47:00 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_data	*data;
	int		i;

	i = -1;
	data = (t_data *)arg;
	while (!data->stop)
	{
		usleep(0);
		if (gettime() - data->last_meal > data->t_die)
		{
			data->philos_dead = 1;
			sem_wait(data->s_printf);
			printf("%lu %d died\n", gettime() - data->t_start, data->philo_id);
			data->stop = 1;
		}
		if (data->num_eat != -1 && data->c_meals == data->num_eat)
			clean_exit(data, 0);
		if (data->philos_dead)
			clean_exit(data, 1);
	}
	return (NULL);
}

void	get_fork(t_data *data)
{
	sem_wait(data->s_fork);
	printf_(data, "has taken a fork");
	sem_wait(data->s_fork);
	printf_(data, "has taken a fork");
	printf_(data, "is eating");
	data->last_meal = gettime();
	ft_sleep(data->t_eat, data);
	sem_post(data->s_fork);
	sem_post(data->s_fork);
}

void	eat_(t_data *data)
{
	if (pthread_create(&data->check_monitor, NULL, check_death, (void *)data))
		ft_error("Error: pthread_create failed", data);
	if (data->philo_id % 2 == 1)
		usleep(100);
	while (!data->stop)
	{
		get_fork(data);
		printf_(data, "is sleeping");
		ft_sleep(data->t_sleep, data);
		printf_(data, "is thinking");
		if (data->num_eat != -1)
		{
			data->c_meals++;
			if (data->c_meals == data->num_eat)
				data->stop = 1;
		}
	}
	if (pthread_join(data->check_monitor, NULL))
		ft_error("Error: pthread_join failed", data);
}

int	main(int ac, char **av)
{
	int		i;
	t_data	*data;

	i = -1;
	if (ac < 5 || ac > 6)
		return (ft_error("Error: invalid number of arguments", NULL));
	init_philos(&data, ac, av);
	data->pid = malloc(sizeof(pid_t) * data->num_philos);
	data->stop = 0;
	data->philos_dead = 0;
	while (++i < data->num_philos)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			ft_error("error on fork\n", data);
		if (data->pid[i] == 0)
		{
			data->philo_id = i + 1;
			data->last_meal = gettime();
			eat_(data);
		}
	}
	exit_p(data);
	return (0);
}
