/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:07:54 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/14 23:30:05 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    safe_mutex(t_mtux *mutex, char *str)
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

void    handell_mutex_error(int status, char *str)
{
    if (status == 0)
        return ;
    else
    {
        // if (status == EBUSY)
        //     printf("The mutex is already locked or referenced by another thread\n");
        // else if (status == EINVAL)
        //     printf("Invalid argument\n");
        if (!ft_strcmp("LOCK", str) || !ft_strcmp("UNLOCK", str))
            ft_error("error on mutex_lock or mutex_unlock\n");
        else if (!ft_strcmp("INIT", str))
            ft_error("error on mutex_init\n");
        else if (!ft_strcmp("DESTROY", str))
            ft_error("error on mutex_destroy\n");
    }
}

void    ft_error(const char *str)
{
    printf ("%s", str);
    exit(EXIT_FAILURE);
}

void    *safe_malloc(size_t size)
{
    void *ret;

    ret = malloc(size);
    if (!ret)
        ft_error("error on malloc\n");
    return (ret);
}