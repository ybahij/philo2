#include "philo.h"

int ft_eat(t_philo *philo)
{
  pthread_mutex_lock(philo->lf);
  if (print_("has taken a fork", philo))
  {
    pthread_mutex_unlock(philo->lf);
    return (1);
  }
  pthread_mutex_lock(philo->rf);
  if (print_("has taken a fork", philo))
  {
    pthread_mutex_unlock(philo->lf);
    pthread_mutex_unlock(philo->rf);
    return (1);
  }
  pthread_mutex_lock(philo->mutex_eat);
  philo->num_eat_count++;
  philo->last_meal = gettime();
  pthread_mutex_unlock(philo->mutex_eat);
  if (print_("is eating", philo))
  {
    pthread_mutex_unlock(philo->lf);
    pthread_mutex_unlock(philo->rf);
    return (1);
  }
  msleep(philo->data->t_eat, philo->data);
  pthread_mutex_unlock(philo->lf);
  pthread_mutex_unlock(philo->rf);
  return (0);
}

int ft_sleep(t_philo *philo)
{
  if (print_("is sleeping", philo))
    return (1);
  msleep(philo->data->t_sleep, philo->data);
  return (0);
}

int ft_think(t_philo *philo)
{
  if (print_("is thinking", philo))
    return (1);
  return (0);
}

void  *routine(void *arg)
{
  t_philo *philo;

  philo = (t_philo *)arg;
  while (1)
  {
    if (ft_eat(philo))
      return (NULL);
    if (ft_sleep(philo))
      return (NULL);
    if (ft_think(philo))
      return (NULL);
  }
}