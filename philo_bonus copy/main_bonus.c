# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
#include <semaphore.h> 
#include <fcntl.h>
#include <signal.h>

typedef struct s_data
{
	int					philo_id;
	long				last_meal;
	long				num_philos;
	long				num_forks;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				philos_dead;
	long				num_eat;
	long				stop;
	long				c_meals;
	pid_t				*pid;
	sem_t	*s_fork;
	sem_t	*s_printf;
	long	t_start;
	pthread_t		check_monitor;
}   t_data;



unsigned long	gettime(void);

int	ft_error(const char *str, t_data *data)
{
    data = NULL;
    if (data != NULL)
	    free(data);
	printf("%s\n", str);
	exit(1);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	printf_(t_data *data, char *str)
{
	sem_wait(data->s_printf);
	if (data->stop)
	{
		sem_post(data->s_printf);
		return ;
	}
	printf("%lu %d %s\n", gettime() - data->t_start, data->philo_id, str);
	sem_post(data->s_printf);
}

int	if_is_digit(const char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

unsigned long	gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(size_t usec, t_data *data)
{
	long	t;

	t = gettime();
	while (!data->stop)
	{
		if (gettime() - t >= usec)
			break ;
		usleep(500);
	}
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
		ft_error("Error: only numeric values are allowed", data);
	if (*str == '-')
		ft_error("Error: only positive values", data);
	else if (*str == '+')
		++str;
	while (*str == '0')
		++str;
	if (*str && !if_is_digit(str))
		ft_error("Error: only numeric values are allowed", data);
	if (*str && ft_strlen(str) > 11)
		ft_error("Error: gerter than INTMAX", data);
	return (str);
}

long	ft_atol(char *s, t_data *data)
{
	const char	*str;
	long		n;
    int INT_MAX;

    INT_MAX = 2147483647;
	n = 0;
	str = valid_str(s, data);
	while (*str >= '0' && *str <= '9')
		n = (n * 10) + (*str++ - '0');
	if (n > INT_MAX)
		ft_error("Error: the value is to big, INTMAX is the limit\n", data);
	return (n);
}

void	init_philos(t_data **philos, int argc, char **argv)
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		ft_error("Error: malloc failed", data);
	data->num_philos = ft_atol(argv[1], data);
	data->num_forks = data->num_philos;
	data->t_die = ft_atol(argv[2], data);
	data->t_eat = ft_atol(argv[3], data);
	data->t_sleep = ft_atol(argv[4], data);
	data->num_eat = -1;
	if (argc == 6)
		data->num_eat = ft_atol(argv[5], data);
	if (data->num_philos < 1 || data->num_philos > 200 || data->t_die == -2 || \
		data->t_eat == -2 || data->t_sleep == -2)
		ft_error("Error: invalid arguments", data);
	data->stop = 0;
	data->c_meals = 0;
	sem_unlink("forks");
	sem_unlink("printf");
	data->s_fork = sem_open("forks", O_CREAT, 0644, data->num_forks);
	data->s_printf = sem_open("printf", O_CREAT, 0644, 1);
	data->t_start = gettime();
	*philos = data;
}

void	*check_death(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!data->stop)
	{
		//usleep(100);
		if (gettime() - data->last_meal > data->t_die)
		{
			data->philos_dead = 1;
			sem_wait(data->s_printf);
			printf("%lu %d died\n", gettime() - data->t_start, data->philo_id);
			sem_post(data->s_printf);
			data->stop = 1;
		}
		if (data->num_eat != -1 && data->c_meals == data->num_eat)
			data->stop = 1;
		if (data->philos_dead)
			exit(1) ;
		if (data->stop)
			exit(0);
	}
	return (NULL);
}

void	eat_(t_data *data)
{
	if (pthread_create(&data->check_monitor, NULL, check_death, (void *)data))
		ft_error("Error: pthread_create failed", data);
	// if (data->philo_id % 2 == 1)
	// 	usleep(1000);
	while (!data->stop)
	{
		sem_wait(data->s_fork);
		printf_(data, "has taken a fork");
		sem_wait(data->s_fork);
		printf_(data, "has taken a fork");
		printf_(data, "is eating");
		data->last_meal = gettime();
		ft_sleep(data->t_eat, data);
		sem_post(data->s_fork);
		printf_(data, "has dropped a fork");
		sem_post(data->s_fork);
		printf_(data, "has dropped a fork");
		printf_(data, "is sleeping");
		ft_sleep(data->t_sleep, data);
		printf_(data, "is thinking");
		if (data->num_eat != -1)
		{
			data->c_meals++;
			if (data->c_meals == data->num_eat)
				data->stop = 1;
		}
	}
	if (pthread_join(data->check_monitor, NULL))
		ft_error("Error: pthread_join failed", data);
}

void	exit_p(t_data *data)
{
	t_data	*tmp;
	int		i;
	int		status;

	tmp = data;
	i = 0;
	while (i < tmp->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < tmp->num_philos)
				kill(tmp->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(tmp->s_printf);
	sem_close(tmp->s_fork);
	sem_unlink("printf");
	sem_unlink("forks");
	free(tmp->pid);
	free(tmp);
}

int main(int ac, char **av)
{
	int i;
	t_data *data;

	i = -1;
	if (ac < 5 || ac > 6)
		return (ft_error("Error: invalid number of arguments", NULL));
	init_philos(&data, ac, av);
	data->pid = malloc(sizeof(pid_t) * data->num_philos);
	data->stop = 0;
	data->philos_dead = 0;
	while (++i < data->num_philos)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			ft_error("error on fork\n", data);
		if (data->pid[i] == 0)
		{
			data->philo_id = i + 1;
			data->last_meal = gettime();
			eat_(data);
		}
	}
	exit_p(data);
	return (0);
}
