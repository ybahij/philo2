/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:51:20 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/18 20:03:26 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    data_init(t_data *data)

{
    int i;

    i = -1;
    // data->laste_meal = safe_malloc(sizeof(long) * data->philo_nbr);
    // data->thread_id = safe_malloc(sizeof(pthread_t) * data->philo_nbr);
    // data->fork = safe_malloc (sizeof(pthread_mutex_t) * data->philo_nbr);
    safe_mutex(&data->w, "INIT");
    safe_mutex(&data->all, "INIT");
    // while (++i < data->philo_nbr)
    //     safe_mutex(&data->fork[i], "INIT");
    data->t_full = 0;
    data->start_simulation = gettime();  
}