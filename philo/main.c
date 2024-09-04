/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssef <youssef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:57:13 by ybahij            #+#    #+#             */
/*   Updated: 2024/09/04 16:10:34 by youssef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (ft_error("Error: ./philo [n_p] [t_d] [t_e] [t_s]", NULL));
	else
	{
		if (init_philos(&data, ac, av) == -1)
			return (1);
		if (start_simulation(&data) == -1)
			return (1);
	}
	return (0);
}
