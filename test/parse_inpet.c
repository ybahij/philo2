/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inpet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:55:54 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/25 16:50:55 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	ft_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

char	*valid_str(char *str, t_data *data)
{
	while (ft_space(*str))
		return (ft_error("only numeric values are allowed\n", data), NULL);
	if (*str == '-')
		return (ft_error("only positive values\n", data), NULL);
	else if (*str == '+')
		++str;
	while (*str == '0')
		++str;
	if (*str && !if_is_digit(str))
		return (ft_error("only numeric values are allowed\n", data), NULL);
	if (*str && ft_strlen(str) > 11)
		return (ft_error("gerter than INTMAX\n", data), NULL);
	return (str);
}

int	parse_inpet(t_data *data, char **av)
{
	data->philo_nbr = ft_atol(av[1], data);
	if (data->philo_nbr == -2)
		return (0);
	data->tm_die = ft_atol(av[2], data);
	if (data->tm_die == -2)
		return (0);
	data->tm_eat = ft_atol(av[3], data);
	if (data->tm_eat == -2)
		return (0);
	data->tm_sleep = ft_atol(av[4], data);
	if (data->tm_sleep == -2)
		return (0);
	if (av[5])
	{
		data->nbr_limit_males = ft_atol(av[5], data);
		if (data->nbr_limit_males == -2)
			return (0);
	}
	else
		data->nbr_limit_males = -1;
	return (1);
}
