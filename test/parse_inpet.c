/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inpet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:55:54 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/17 16:39:36 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const char *valid_str(const char *str)
{
    while (ft_space(*str))
        ++str;
    if (*str == '+')
        ++str;
    else if (*str == '-')
        ft_error("only postef value\n");
    while (*str == '0')
        ++str;
    if (*str && !if_is_digit(str))
        ft_error("wrong input\n");
    if (*str && ft_strlen(str) > 11)
        ft_error("gerter than INTMAX\n");
    return (str);
}

void    parse_inpet(t_data *data, char **av)
{
    data->philo_nbr = ft_atol(av[1]);
    data->tm_die = ft_atol(av[2]);
    data->tm_eat = ft_atol(av[3]);
    data->tm_sleep = ft_atol(av[4]);
    if (av[5])
        data->nbr_limit_males = ft_atol(av[5]);
    else    
        data->nbr_limit_males = -1;
    
}