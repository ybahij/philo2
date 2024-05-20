/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:07:54 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/19 22:21:09 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_mutex(t_mtux *mutex, char *str)
{
	if (!mutex)
		return ;
	if (!ft_strcmp("LOCK", str))
		handell_mutex_error(pthread_mutex_lock(mutex), "LOCK");
	else if (!ft_strcmp("UNLOCK", str))
		handell_mutex_error(pthread_mutex_unlock(mutex), "UNLOCK");
	else if (!ft_strcmp("INIT", str))
		handell_mutex_error(pthread_mutex_init(mutex, NULL), "INIT");
	else if (!ft_strcmp("DESTROY", str))
		handell_mutex_error(pthread_mutex_destroy(mutex), "DESTROY");
}

void	handell_mutex_error(int status, char *str)
{
	if (status == 0)
		return ;
	else
	{
		if (!ft_strcmp("LOCK", str) || !ft_strcmp("UNLOCK", str))
			ft_phtread_error("error on mutex_lock or mutex_unlock\n");
		else if (!ft_strcmp("INIT", str))
			ft_phtread_error("error on mutex_init\n");
		else if (!ft_strcmp("DESTROY", str))
			ft_phtread_error("error on mutex_destroy\n");
	}
}

void	*safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		ft_phtread_error("error on malloc\n");
	return (ret);
}
