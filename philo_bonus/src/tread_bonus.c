/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tread_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:02:55 by mjhin             #+#    #+#             */
/*   Updated: 2022/03/09 13:56:59 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	*check_dead_eat(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!(ft_time_ms() - philo->t_last_eat < (long int)philo->data->t_dead))
		{
			print_str("died", philo, 2);
			exit (10);
		}
		usleep(100);
		if (philo->data->n_eat != -1 && philo->n_eat >= philo->data->n_eat)
			break ;
	}
	return (NULL);
}

static void	philo_eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_str("has taken a fork", philo, 0);
	sem_wait(philo->data->forks);
	print_str("has taken a fork", philo, 0);
	print_str("is eating", philo, 1);
	ft_usleep(philo->data->t_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	*philo_fork(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_create(&philo->thread_id, NULL, check_dead_eat, (void *)philo);
	if (philo->data->n_philos == 1)
	{
		print_str("has taken a fork", philo, 0);
		ft_usleep(philo->data->t_dead);
	}
	else
	{
		if (philo->id % 2 == 0)
			usleep(500);
		while (!philo->data->dead)
		{
			philo_eat(philo);
			if (philo->data->n_eat != -1 && philo->n_eat >= philo->data->n_eat)
				break ;
			print_str("is sleeping", philo, 0);
			ft_usleep(philo->data->t_sleep);
			print_str("is thinking", philo, 0);
		}
	}
	pthread_join(philo->thread_id, NULL);
	exit (0);
}

int	fork_create(t_data *data)
{
	size_t	i;

	i = 0;
	data->time_all = 0;
	data->time_all = ft_time_ms();
	data->dead = 0;
	while (i < data->n_philos)
	{
		data->philos[i].t_last_eat = data->time_all;
		data->philos[i].pid_fil = fork();
		if (data->philos[i].pid_fil == -1)
			return (1);
		if (data->philos[i].pid_fil == 0)
			philo_fork((void *)&data->philos[i]);
		i++;
	}
	return (0);
}
