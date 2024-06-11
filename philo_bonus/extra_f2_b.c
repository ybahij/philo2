/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f2_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:16:59 by ybahij            #+#    #+#             */
/*   Updated: 2024/06/08 15:02:42 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sleep(size_t usec, t_data *data)
{
	size_t	t;

	t = gettime();
	while (!data->stop)
	{
		if (gettime() - t >= usec)
			break ;
		usleep(500);
	}
}

int	ft_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

char	*valid_str(char *str, t_data *data)
{
	while (ft_space(*str))
		ft_error("Error: only numeric values are allowed", data);
	if (*str == '-')
		ft_error("Error: only positive values", data);
	else if (*str == '+')
		++str;
	while (*str == '0')
		++str;
	if (*str && !if_is_digit(str))
		ft_error("Error: only numeric values are allowed", data);
	if (*str && ft_strlen(str) > 11)
		ft_error("Error: gerter than INTMAX", data);
	return (str);
}

long	ft_atol(char *s, t_data *data)
{
	const char	*str;
	long		n;
	int			int_max;

	int_max = 2147483647;
	n = 0;
	str = valid_str(s, data);
	while (*str >= '0' && *str <= '9')
		n = (n * 10) + (*str++ - '0');
	if (n > int_max)
		ft_error("Error: the value is to big, INTMAX is the limit\n", data);
	return (n);
}

void	init_philos(t_data **philos, int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_error("Error: malloc failed", data);
	data->num_philos = ft_atol(argv[1], data);
	data->num_forks = data->num_philos;
	data->t_die = ft_atol(argv[2], data);
	data->t_eat = ft_atol(argv[3], data);
	data->t_sleep = ft_atol(argv[4], data);
	data->num_eat = -1;
	if (argc == 6)
		data->num_eat = ft_atol(argv[5], data);
	if (data->num_philos < 1 || data->num_philos > 200 || data->t_die == -2 || \
		data->t_eat == -2 || data->t_sleep == -2)
		ft_error("Error: invalid arguments", data);
	data->stop = 0;
	data->c_meals = 0;
	sem_unlink("forks");
	sem_unlink("printf");
	data->s_fork = sem_open("forks", O_CREAT, 0644, data->num_forks);
	data->s_printf = sem_open("printf", O_CREAT, 0644, 1);
	data->t_start = gettime();
	*philos = data;
}
