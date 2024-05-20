/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:06:15 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/19 22:23:14 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat_simulation(t_data *philo)
{
	int	id;

	pthread_mutex_lock(&philo->all);
	id = philo->philo_id;
	pthread_mutex_unlock(&philo->all);
	while (1)
	{
		if (philo->end_simulation == 1)
			break ;
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

void	*cheak_death(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->philo_nbr)
		{
			if (data->cheak == 0)
				break ;
			if (data->nbr_limit_males != -1 && (size_t)data->philo_nbr
				* (size_t)data->nbr_limit_males <= data->t_full)
			{
				data->end_simulation = 1;
				return (NULL);
			}
			if (gettime() - data->laste_meal[i] >= (size_t)data->tm_die)
			{
				ft_printf("%ld: the philo [%d] dead\n", i, data);
				data->end_simulation = 1;
				return (NULL);
			}
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	data = safe_malloc(sizeof(t_data));
	i = -1;
	if (ac != 5 && ac != 6)
		ft_error("./philo [n_of_p] [t_t_d] [t_t_e] [t_t_s]\n", data);
	parse_inpet(data, av);
	data_init(data);
	i = -1;
	data->cheak = 0;
	pthread_create(&data->cheaker, NULL, (void *)cheak_death, data);
	while (++i < data->philo_nbr)
	{
		data->philo_id = i;
		data->laste_meal[i] = gettime();
		pthread_create(&data->thread_id[i], NULL, (void *)eat_simulation, data);
		usleep(200);
	}
	data->cheak = 1;
	i = -1;
	while (++i < data->philo_nbr)
		safe_thread(&data->thread_id[i], NULL, NULL, "join");
	clean_m(data);
	return (0);
}
