/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:07:54 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/25 06:12:42 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_mutex(t_mtux *mutex, char *str)
{
	if (!mutex)
		return (1);
	if (!ft_strcmp("LOCK", str))
		return (handell_mutex_error(pthread_mutex_lock(mutex), "LOCK"));
	else if (!ft_strcmp("UNLOCK", str))
		return (handell_mutex_error(pthread_mutex_unlock(mutex), "UNLOCK"));
	else if (!ft_strcmp("INIT", str))
		return (handell_mutex_error(pthread_mutex_init(mutex, NULL), "INIT"));
	else if (!ft_strcmp("DESTROY", str))
		return (handell_mutex_error(pthread_mutex_destroy(mutex), "DESTROY"));
	return (1);
}

int	handell_mutex_error(int status, char *str)
{
	if (status != 0)
	{
		if (!ft_strcmp("LOCK", str) || !ft_strcmp("UNLOCK", str))
			return (ft_phtread_error("error on mutex_lock or mutex_unlock\n"));
		else if (!ft_strcmp("INIT", str))
			return (ft_phtread_error("error on mutex_init\n"));
		else if (!ft_strcmp("DESTROY", str))
			return (ft_phtread_error("error on mutex_destroy\n"));
	}
	return (1);
}

void	*safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		ft_phtread_error("error on malloc\n");
	return (ret);
}
