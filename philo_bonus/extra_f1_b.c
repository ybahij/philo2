/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f1_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:15:35 by ybahij            #+#    #+#             */
/*   Updated: 2024/06/08 15:01:07 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(const char *str, t_data *data)
{
	data = NULL;
	if (data != NULL)
		free(data);
	printf("%s\n", str);
	exit(1);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	printf_(t_data *data, char *str)
{
	sem_wait(data->s_printf);
	if (data->stop)
	{
		sem_post(data->s_printf);
		return ;
	}
	printf("%lu %d %s\n", gettime() - data->t_start, data->philo_id, str);
	sem_post(data->s_printf);
}

int	if_is_digit(const char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

long	gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
