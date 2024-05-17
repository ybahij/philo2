/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:51:20 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/17 18:44:41 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void    assign_fork(t_philo *philo, int philo_p)
// {
//     int philo_nbr;
    
//     philo_nbr = philo->data->philo_nbr;    
    
    // philo[philo_p].first_fork = &philo->data->forks[(philo_p + 1) % philo_nbr];
    // philo[philo_p].second_fork = &philo->data->forks[philo_p];
    // if (philo->philo_id % 2)
    // {
    //     philo[philo_p].first_fork = &philo->data->forks[philo_p];
    //     philo[philo_p].second_fork = &philo->data->forks[(philo_p + 1) % philo_nbr];
    // }
// }

// void philo_init(t_data *data, t_philo *philo)
// {
//     int i;

//     i = -1;
//     while (++i < data->philo_nbr)
//         data->forks[i].fork_id = i;
//     i = -1;
//     while (++i < data->philo_nbr)
//     {
//         philo[i].philo_id = i + 1;
//         philo[i].meals_c = 0;
//         philo[i].data = data;
//         assign_fork(philo, i);
//     }
// }

void    data_init(t_data *data)
{
    int i;

    i = -1;
    data->laste_meal = safe_malloc(sizeof(long) * data->philo_nbr);
    data->thread_id = safe_malloc(sizeof(pthread_t) * data->philo_nbr);
    data->fork = safe_malloc (sizeof(pthread_mutex_t) * data->philo_nbr);
    safe_mutex(&data->w, "INIT");
    safe_mutex(&data->all, "INIT");
    while (++i < data->philo_nbr)
        safe_mutex(&data->fork[i], "INIT");
    data->t_full = 0;
    data->start_simulation = gettime();  
}