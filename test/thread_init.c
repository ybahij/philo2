/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:17:14 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/06 22:47:47 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    handell_thread_error(int status, char *str)
{
    if (status == 0)
        return ;
    else
    {
       if (status == EAGAIN) {
            printf("Insufficient resources to create another thread\n");
        } else if (status == EINVAL) {
            printf("Invalid thread attributes\n");
        } 
        if (!ft_strcmp("creat", str))
            ft_error("error on pthread_creat\n");
        else if (!ft_strcmp("join", str))
            ft_error("error on mutex_join\n");
        else if (!ft_strcmp("detach", str))
            ft_error("error on mutex_detach\n");
    }
}

void    safe_thread(pthread_t  *thr, void *(*handeler)(void *), void *data, char *str)
{
    if (!ft_strcmp("creat", str))
        handell_thread_error(pthread_create(thr, NULL, handeler, data), "creat");
    else if (!ft_strcmp("join", str))
        handell_thread_error(pthread_join(*thr, NULL), "join");
    else if (!ft_strcmp("detach", str))
        handell_thread_error(pthread_detach(*thr), "detach");
}