/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonuss.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:45:27 by afanti            #+#    #+#             */
/*   Updated: 2023/03/14 11:37:47 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	main_nextnext(t_data *data, char **av, int i)
{
	if (data->av_nbr == i)
	{
		data->here = 0;
		data->here = ft_memcmp(av[1], "here_doc", ft_strlen("here_doc"));
		if (data->here != 0)
			data->fd_stdout = open(av[data->c], O_CREAT
					| O_RDWR | O_TRUNC, 0777);
		if (data->here == 0)
			data->fd_stdout = open(av[data->c], O_CREAT
					| O_RDWR | O_APPEND, 0777);
		if (data->fd_stdout < 0)
			error_fd(av[data->c]);
		dup2(data->fd_stdout, STDOUT_FILENO);
	}
}

void	main_next1(t_data *data, char **av, int i)
{
	int	d;

	d = 0;
	if (i == 0)
	{
		d = ft_memcmp(av[1], "here_doc", ft_strlen(av[1]) + 1);
		if (d == 0)
			complit_here(data, d, av);
		else if (d != 0)
			main_next11(data, av);
	}
	else
		dup2(data->pipes[1], STDOUT_FILENO);
	data->av_x = ft_split(av[data->d], ' ');
	data->i = 0;
	main_nextnext(data, av, i);
	if (access(data->av_x[0], X_OK) == 0)
		execve(data->av_x[0], data->av_x, NULL);
	check_av(av[data->d]);
}

void	main_next2(t_data *data, char **av, char **env)
{
	while (env[data->i])
	{
		if (env[data->i][0] == 'P' && env[data->i][3] == 'H')
			data->path_x = env[data->i];
		data->i++;
	}
	if (data->path_x == NULL)
		error_cmd(av[data->d]);
	data->path2d_x = ft_split(data->path_x + 5, ':');
	data->i = 0;
	while (data->path2d_x[data->i])
	{
		if (data->av_x[0][0] == '/')
			error_cmd(data->av_x[0]);
		data->command_x = ft_strjoin(data->path2d_x[data->i], "/");
		data->command_x = ft_strjoin(data->command_x, data->av_x[0]);
		if (access(data->command_x, X_OK) != -1)
			execve(data->command_x, data->av_x, env);
		free(data->command_x);
		data->i++;
	}
	error_cmd(data->av_x[0]);
}

void	close_pipes(t_data *data)
{
	close(data->pipes[1]);
	dup2(data->pipes[0], STDIN_FILENO);
	close(data->pipes[0]);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->av_nbr = ac - 4;
	data->c = ac - 1;
	data->d = 2;
	main_next(av, env, i, data);
	waitpid(data->pid, NULL, 0);
	wait(NULL);
}
