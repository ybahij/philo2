/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:47:03 by ybahij            #+#    #+#             */
/*   Updated: 2024/06/04 16:44:30 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	long				num_philos;
	long				num_forks;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				num_eat;
	long				stop;
	long				s_cheak;
	long				c_meals;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_meals;
	pthread_mutex_t	mutex_printf;
	long	t_start;
	pthread_t		check_monitor;
}t_data;

typedef struct s_philo
{
	int				index;
	int				num_eat_count;
	long	t_meal;
	t_data			*data;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rf;
	pthread_t		pth_t;
}t_philo;

int	ft_error(const char *str, t_data *data);
int	ft_strlen(const char *str);
int	if_is_digit(const char *str);
long	gettime(void);
void	ft_sleep(size_t usec, t_data *data);
int	ft_space(char c);
char	*valid_str(char *str, t_data *data);
long	ft_atol(char *s, t_data *data);
int	init_data(t_data **data, int argc, char **argv);
int	init_mutex_fork(t_data *data);
void	init_philo(t_philo *philo, int i, \
						t_data *data, pthread_mutex_t *forks);
int	init_philos(t_philo **philos, int argc, char **argv);
int 	print_(char *msg, t_philo *philo);
int	get_fork(t_philo *philo);
void	*eat_(void *args);
void	*monitor(void *args);
int start_simulation(t_philo *philos);


#endif

