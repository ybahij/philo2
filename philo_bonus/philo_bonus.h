/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:18:37 by ybahij            #+#    #+#             */
/*   Updated: 2024/06/09 20:14:26 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int			philo_id;
	long		last_meal;
	long		num_philos;
	long		num_forks;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	long		philos_dead;
	long		num_eat;
	long		stop;
	long		c_meals;
	pid_t		*pid;
	sem_t		*s_fork;
	sem_t		*s_printf;
	long		t_start;
	pthread_t	check_monitor;
}				t_data;

void			*check_death(void *arg);
void			eat_(t_data *data);
void			exit_p(t_data *data);
void			ft_sleep(size_t usec, t_data *data);
int				ft_space(char c);
char			*valid_str(char *str, t_data *data);
long			ft_atol(char *s, t_data *data);
void			init_philos(t_data **philos, int argc, char **argv);
int				ft_error(const char *str, t_data *data);
int				ft_strlen(const char *str);
void			printf_(t_data *data, char *str);
int				if_is_digit(const char *str);
long			gettime(void);
void			clean_exit(t_data *data, int i);

#endif