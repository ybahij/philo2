/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:46:57 by ybahij            #+#    #+#             */
/*   Updated: 2024/05/17 18:36:33 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

typedef pthread_mutex_t t_mtux;

typedef struct s_fork
{
    t_mtux fork;
    int     fork_id;
}   t_fork;

typedef struct s_data t_data;

typedef struct s_philo
{
    int     philo_id; 
    t_mtux  *first_fork;
    t_mtux  *second_fork;
    t_data *data;
    
}   t_philo;  


typedef struct s_data
{
    long philo_nbr;
    long tm_die;
    long tm_eat;
    long tm_sleep;
    long nbr_limit_males;
    long    end_simulation;
    long     start_simulation;
    int     c_malec;
    int     philo_id;
    long    *laste_meal;
    t_mtux  w;
    t_mtux  all;
    t_mtux *fork;
    t_mtux  first_fork;
    t_mtux  second_fork;

    int     t_full;
    pthread_t   *thread_id;
    pthread_t   cheaker;
    //t_philo *philo;

}   t_data;

//===============thread_init==============//
void    handell_thread_error(int status, char *str);
void    safe_thread(pthread_t  *thr, void *(*handeler)(void *), void *data, char *str);
//===============data_init================//
void    data_init(t_data *data);
unsigned long gettime(void);
// void    assign_fork(t_philo *philo, int philo_p);
// void    philo_init(t_data *data, t_philo *philo);
//===============extra===================//
void    ft_error(const char *str);
const char *valid_str(const char *str);
void    *safe_malloc(size_t size);
int     ft_strlen(const char *str);
int     ft_space(char c);
int     ft_strcmp(const char *s1, const char *s2);
void    handell_mutex_error(int status, char *str);
void    safe_mutex(t_mtux *mutex, char *str);
int     if_is_digit(const char *str);
long    ft_atol(const char *s);
void    parse_inpet(t_data *data, char **av);
int full_mals(t_philo *philo);

#endif