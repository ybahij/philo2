/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:06:15 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/19 16:47:15 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    clean_m(t_data *d)
{
    // int i;

    // i = -1;
    // while (++i < d->philo_nbr)
    // {
    //     safe_mutex(&d->fork[i], "DESTROY");
    // }
    // safe_mutex(&d->w, "DESTROY");
	// safe_mutex(&d->all, "DESTROY");
    free(d->fork);
	free(d->laste_meal);
	free(d->thread_id);
    free(d);
}
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
	ft_printf("%ld: philo n[%d] take the scond fork\n", id, data);
	ft_printf("%ld: the philo n:[%d] is eating\n", id, data);
	pthread_mutex_lock(&data->m_eat);
	data->laste_meal[id] = gettime();
	pthread_mutex_unlock(&data->m_eat);
	ft_sleep(data->tm_eat, data);
	pthread_mutex_unlock(&data->fork[id]);
	pthread_mutex_unlock(&data->fork[(id + 1) % data->philo_nbr]);	
}

void	*eat_simulation(t_data *philo)
{
	int	id;

	pthread_mutex_lock(&philo->all);
	id = philo->philo_id;
	pthread_mutex_unlock(&philo->all);
	while (1)
	{
		get_forke(philo, id);
		
		pthread_mutex_lock(&philo->t_eat);
		philo->t_full++;
		pthread_mutex_unlock(&philo->t_eat);
		ft_printf("%ld: the philo n:[%d] is sleping\n", id, philo);
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
		i = -1;
		while (++i < data->philo_nbr)
		{
			pthread_mutex_lock(&data->all);
			if (data->nbr_limit_males != -1 && (size_t)data->philo_nbr
				* (size_t)data->nbr_limit_males <= data->t_full)
			{	
				pthread_mutex_unlock(&data->all);
				return (clean_m(data), 1);
			}	
			if (gettime() - data->laste_meal[i] >= (size_t)data->tm_die)
			{
				ft_printf("%ld: the philo [%d] dead\n", i, data);
				pthread_mutex_unlock(&data->all);
				return (clean_m(data), 1);
			}
			pthread_mutex_unlock(&data->all);
		}
	}
	return (1);
}

void	ft_bzero(void *s, size_t n)
{
	memset(s, 0, n);
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
	data->laste_meal = safe_malloc(sizeof(long) * data->philo_nbr);
    data->thread_id = safe_malloc(sizeof(pthread_t) * data->philo_nbr);
    data->fork = safe_malloc (sizeof(pthread_mutex_t) * data->philo_nbr);
	data_init(data);
	while (++i < data->philo_nbr)
        safe_mutex(&data->fork[i], "INIT");
	i = -1;
	while (++i < data->philo_nbr)
	{
		data->philo_id = i;
		data->laste_meal[i] = gettime();
		pthread_create(&data->thread_id[i], NULL, (void *)eat_simulation, data);
		usleep(100);
	}
	cheak_death(data);
	return (0);
}