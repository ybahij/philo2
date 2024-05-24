/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:17:14 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/24 22:05:21 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handell_thread_error(int status, char *str)
{
	if (status == 0)
		return ;
	else
	{
		if (!ft_strcmp("creat", str))
			ft_phtread_error("error on pthread_creat\n");
		else if (!ft_strcmp("join", str))
			ft_phtread_error("error on phtread_join\n");
		else if (!ft_strcmp("detach", str))
			ft_phtread_error("error on phtread_detach\n");
	}
}

void	safe_thread(pthread_t *thr, void *(*handeler)(void *), void *data,
		char *str)
{
	if (!ft_strcmp("creat", str))
		handell_thread_error(pthread_create(thr, NULL, handeler, data),
			"creat");
	else if (!ft_strcmp("join", str))
		handell_thread_error(pthread_join(*thr, NULL), "join");
	else if (!ft_strcmp("detach", str))
		handell_thread_error(pthread_detach(*thr), "detach");
}

unsigned long	gettime(void)
{
	struct timeval	tv;
	size_t			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_sleep(size_t usec)
{
	size_t	t_zero;
	size_t	timer;

	t_zero = gettime();
	timer = (usec * 1000) - 5000;
	usleep(timer);
	while (gettime() - t_zero < usec)
		usleep(10);
}
