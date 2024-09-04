#include "philo.h"

int all_philos_finished_eating(t_data *data)
{
  int i;

  i = -1;
  while (++i < data->num_philos)
  {
    pthread_mutex_lock(data->philos[i]->mutex_eat);
    if (data->philos[i]->num_eat_count < data->num_eat)
    {
      pthread_mutex_unlock(data->philos[i]->mutex_eat);
      return (0);
    }
    pthread_mutex_unlock(data->philos[i]->mutex_eat);
  }
  pthread_mutex_lock(data->mutex_s_over);
  data->s_over = 1;
  pthread_mutex_unlock(data->mutex_s_over);
  return (1);
}

int any_philo_starved(t_data *data)
{
  int i;

  i = -1;
  printf("start_simulation2\n");

  while (++i < data->num_philos)
  {
    pthread_mutex_lock(data->philos[i]->mutex_eat);
    if (gettime() - data->philos[i]->last_meal > data->t_die)
    {
      pthread_mutex_lock(&data->mutex_printf);
      printf("%ld %d died\n", gettime() - data->t_start, data->philos[i]->index);
      pthread_mutex_unlock(&data->mutex_printf);
      pthread_mutex_lock(data->mutex_s_over);
      data->s_over = 1;
      pthread_mutex_unlock(data->mutex_s_over);
      pthread_mutex_unlock(data->philos[i]->mutex_eat);
      return (1);
    }
    pthread_mutex_unlock(data->philos[i]->mutex_eat);
  }
  return (0);
}

void  monitor(t_data *data)
{
  while (1)
  {
    if (all_philos_finished_eating(data))
      return ;
    printf("start_simulation5\n");
    if (any_philo_starved(data))
      return ;
    printf("start_simulation5\n");
  }
}

int start_simulation(t_data *data)
{
  int i;
  // int j;

  i = -1;
  data->t_start = gettime();
  while(++i < data->num_philos)
    pthread_create(&data->philos[i]->pth_t, NULL, routine, data->philos[i]);
  monitor(data);
  // j = -1;
  // while(++j < i)
  //   pthread_join(data->philos[j]->pth_t, NULL);
  // exit_philo(data);
  return (0);
}