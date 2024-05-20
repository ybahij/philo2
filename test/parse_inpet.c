/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inpet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:55:54 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/19 22:23:40 by ybahij           ###   ########.fr       */
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
		ft_error("only numeric values are allowed\n", data);
	if (*str == '+')
		++str;
	else if (*str == '-')
		ft_error("only positive values\n", data);
	while (*str == '0')
		++str;
	if (*str && !if_is_digit(str))
		ft_error("only numeric values are allowed\n", data);
	if (*str && ft_strlen(str) > 11)
		ft_error("gerter than INTMAX\n", data);
	return (str);
}

void	parse_inpet(t_data *data, char **av)
{
	data->philo_nbr = ft_atol(av[1], data);
	if (data->philo_nbr > 200)
		ft_error("can't be more than 200 philo\n", data);
	data->tm_die = ft_atol(av[2], data);
	data->tm_eat = ft_atol(av[3], data);
	data->tm_sleep = ft_atol(av[4], data);
	if (data->tm_die < 60 || data->tm_eat < 60 || data->tm_sleep < 60)
		ft_error("should be more than 60 ms\n", data);
	if (av[5])
		data->nbr_limit_males = ft_atol(av[5], data);
	else
		data->nbr_limit_males = -1;
}
