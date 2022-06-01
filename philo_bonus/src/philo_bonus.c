/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:04:11 by mjhin             #+#    #+#             */
/*   Updated: 2022/03/09 13:57:37 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	exit_philo(t_data *data)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < data->n_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 10)
		{
			i = -1;
			while (++i < data->n_philos)
				kill(data->philos[i].pid_fil, SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(data->print);
	sem_close(data->forks);
	sem_unlink("sem_print");
	sem_unlink("sem_forks");
	free(data->philos);
}

void	semafors_init(t_data *data)
{
	sem_unlink("sem_print");
	sem_unlink("sem_forks");
	data->print = sem_open("sem_print", O_CREAT, 0644, 1);
	data->forks = sem_open("sem_forks", O_CREAT, 0644, data->n_philos);
	if (data->print == SEM_FAILED || data->forks == SEM_FAILED)
	{
		if (data->print != SEM_FAILED)
			sem_close(data->print);
		if (data->forks != SEM_FAILED)
			sem_close(data->forks);
		sem_unlink("sem_print");
		sem_unlink("sem_forks");
		exit(ft_exit("Bad sem init!", 4));
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_exit("Bad arguments!", 1));
	if (check_init(argc, argv, &data))
		return (ft_exit("Bad init argument!", 2));
	semafors_init(&data);
	if (fork_create(&data))
	{
		ft_exit("Bad fork create!", 3);
		exit_philo(&data);
		return (3);
	}
	exit_philo(&data);
	return (0);
}
