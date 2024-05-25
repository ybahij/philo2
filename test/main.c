/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:06:15 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/25 16:41:05 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	full_(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		if (data->t_full[i] != data->nbr_limit_males)
			return (1);
	}
	return (0);
}

void	*eat_simulation(t_data *philo)
{
	int	id;

	pthread_mutex_lock(&philo->id);
	id = philo->philo_id;
	pthread_mutex_unlock(&philo->id);
	while (philo->end_simulation != 1)
	{
		if (philo->nbr_limit_males != -1
			&& philo->t_full[id] == philo->nbr_limit_males)
			break ;
		get_forke(philo, id);
		pthread_mutex_lock(&philo->t_eat);
		philo->t_full[id]++;
		pthread_mutex_unlock(&philo->t_eat);
		if (philo->end_simulation == 1)
			break ;
		ft_printf("%ld: the philo n:[%d] is sleping\n", id, philo);
		ft_sleep(philo->tm_sleep);
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
			if (data->nbr_limit_males != -1 && !full_(data))
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

int	parse_init(t_data *data, char **av)
{
	if (!parse_inpet(data, av))
		return (0);
	data_init(data);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	data = safe_malloc(sizeof(t_data));
	i = -1;
	if (ac != 5 && ac != 6)
		ft_error("./philo [n_of_p] [t_t_d] [t_t_e] [t_t_s]\n", data);
	if (!parse_init(data, av))
		return (1);
	data->cheak = 0;
	pthread_create(&data->cheaker, NULL, (void *)cheak_death, data);
	while (++i < data->philo_nbr)
	{
		data->philo_id = i;
		data->laste_meal[i] = gettime();
		if (pthread_create(&data->thread_id[i], NULL, (void *)eat_simulation,
				data) != 0)
			return (clean_m(data), 1);
		usleep(100);
	}
	data->cheak = 1;
	i = -1;
	while (++i < data->philo_nbr)
		safe_thread(&data->thread_id[i], NULL, NULL, "join");
	return (clean_m(data), 0);
}
