/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:46:57 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/25 06:21:52 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mtux;

typedef struct s_data
{
	long				philo_nbr;
	long				tm_die;
	long				tm_eat;
	long				tm_sleep;
	long				nbr_limit_males;
	long				end_simulation;
	long				start_simulation;
	int					c_malec;
	int					philo_id;
	long				*laste_meal;
	t_mtux				w;
	t_mtux				m_eat;
	t_mtux				t_eat;
	int					cheak;
	t_mtux				id;
	t_mtux				*fork;
	t_mtux				first_fork;
	t_mtux				second_fork;
	int					*t_full;
	pthread_t			*thread_id;
	pthread_t			cheaker;

}						t_data;

void					ft_printf(char *msg, int id, t_data *data);
void					handell_thread_error(int status, char *str);
void					safe_thread(pthread_t *thr, void *(*handeler)(void *),
							void *data, char *str);
void					data_init(t_data *data);
unsigned long			gettime(void);
void					clean_m(t_data *d);
void					get_forke(t_data *data, int id);
int						ft_error(const char *str, t_data *data);
int						ft_phtread_error(const char *str);
char					*valid_str(char *str, t_data *data);
void					*safe_malloc(size_t size);
int						ft_strlen(const char *str);
int						ft_space(char c);
unsigned long			gettime(void);
void					ft_sleep(size_t usec);
int						ft_strcmp(const char *s1, const char *s2);
int						handell_mutex_error(int status, char *str);
int						safe_mutex(t_mtux *mutex, char *str);
int						if_is_digit(const char *str);
long					ft_atol(char *s, t_data *data);
int						parse_inpet(t_data *data, char **av);
int						full_(t_data *data);
int						parse_init(t_data *data, char **av);

#endif