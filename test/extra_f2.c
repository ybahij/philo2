/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:58:23 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/24 17:07:33 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_phtread_error(const char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}

void	ft_error(const char *str, t_data *data)
{
	free(data);
	printf("%s", str);
	exit(EXIT_FAILURE);
}

void	clean_m(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->philo_nbr)
	{
		safe_mutex(&d->fork[i], "DESTROY");
	}
	safe_mutex(&d->w, "DESTROY");
	safe_mutex(&d->id, "DESTROY");
	safe_mutex(&d->m_eat, "DESTROY");
	safe_mutex(&d->t_eat, "DESTROY");
	safe_mutex(&d->first_fork, "DESTROY");
	safe_mutex(&d->second_fork, "DESTROY");
	free(d->fork);
	free(d->t_full);
	free(d->laste_meal);
	free(d->thread_id);
	free(d);
}
