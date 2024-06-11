/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:56:08 by ybahij            #+#    #+#             */
/*   Updated: 2024/06/10 04:10:35 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(const char *str, t_data *data)
{
	data = NULL;
	if (data != NULL)
		free(data);
	printf("%s\n", str);
	return (-2);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

void	ft_sleep(size_t usec, t_data *data)
{
	size_t	t;

	t = gettime();
	while (!ft_stop(data->philos))
	{
		if (gettime() - t >= usec)
			break ;
		usleep(10);
	}
}
