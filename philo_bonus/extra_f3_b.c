/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_f3_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 23:26:31 by ybahij            #+#    #+#             */
/*   Updated: 2024/06/09 20:14:09 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_exit(t_data *data, int i)
{
	free (data->pid);
	free (data);
	exit(i);
}

void	exit_p(t_data *data)
{
	t_data	*tmp;
	int		i;
	int		status;

	tmp = data;
	i = -1;
	status = 0;
	while (++i < tmp->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status)
		{
			i = -1;
			while (++i < tmp->num_philos)
				kill(tmp->pid[i], SIGKILL);
			break ;
		}
	}
	sem_close(tmp->s_printf);
	sem_close(tmp->s_fork);
	sem_unlink("printf");
	sem_unlink("forks");
	free(tmp->pid);
	free(tmp);
}
