/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:06:15 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/17 18:47:29 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void    clean_m(t_philo *p,t_data *d)
// {
//     int i;

//     i = -1;
//     while (++i < p->data->philo_nbr)
//     {
//         safe_mutex(&p->data->forks[i].fork, "DESTROY");
//     }
//     safe_mutex(&p->data->w, "DESTROY");
//     free(d->forks);
//     free(p);
// }
unsigned long	gettime(void)
{
	struct timeval	tv;
	size_t			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_sleep(long usec, t_data *data)
{
	time_t	t_zero;
	size_t	timer;

	t_zero = gettime();
	timer = (usec * 1000) - 5000;
	usleep(timer);
	while (gettime() - t_zero < usec)
		usleep(10);
}

void	ft_printf(char *msg, int id, t_data *data)
{
	pthread_mutex_lock(&data->w);
	printf(msg, gettime() - data->start_simulation, id + 1);
	pthread_mutex_unlock(&data->w);
}

void	get_forke(t_data *data, int id)
{
	pthread_mutex_lock(&data->fork[id]);
	ft_printf("%ld: philo n[%d] take the first fork\n", id, data);
	pthread_mutex_lock(&data->fork[(id + 1) % data->philo_nbr]);
	pthread_mutex_lock(&data->all);
	data->laste_meal[id] = gettime();
	pthread_mutex_unlock(&data->all);
	ft_printf("%ld: philo n[%d] take the scond fork\n", id, data);
	ft_printf("%ld: the philo n:[%d] is eating\n", id, data);
	ft_sleep(data->tm_eat, data);
}

void	*eat_simulation(t_data *philo)
{
	int	id;

	pthread_mutex_lock(&philo->all);
	id = philo->philo_id;
	philo->laste_meal[id] = gettime();
	pthread_mutex_unlock(&philo->all);
	while (1)
	{
		get_forke(philo, id);
		pthread_mutex_unlock(&philo->fork[id]);
		pthread_mutex_unlock(&philo->fork[(id + 1) % philo->philo_nbr]);
		pthread_mutex_lock(&philo->all);
		philo->t_full++;
		ft_printf("%ld: the philo n:[%d] is sleping\n", id, philo);
		pthread_mutex_unlock(&philo->all);
		ft_sleep(philo->tm_sleep, philo);
		ft_printf("%ld: the philo n:[%d] is thinking\n", id, philo);
	}
	return (NULL);
}

int	cheak_death(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			pthread_mutex_lock(&data->all);
			if (data->nbr_limit_males != -1 && (size_t)data->philo_nbr
				* (size_t)data->nbr_limit_males <= data->t_full)
				return (1);
			if (gettime() - data->laste_meal[i] >= (size_t)data->tm_die)
			{
				ft_printf("%ld: the philo [%d] dead\n", i, data);
				return (1);
			}
			pthread_mutex_unlock(&data->all);
			i++;
		}
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data *data;
	int i;

	i = -1;
	if (ac != 5 && ac != 6)
		ft_error("wrong format\n");
	data = safe_malloc(sizeof(t_data));
	parse_inpet(data, av);
	data_init(data);
	while (++i < data->philo_nbr)
	{
		pthread_mutex_lock(&data->all);
		data->philo_id = i;
		pthread_mutex_unlock(&data->all);
		pthread_create(&data->thread_id[i], NULL, (void *)eat_simulation, data);
		usleep(60);
	}
	return (cheak_death(data));
}