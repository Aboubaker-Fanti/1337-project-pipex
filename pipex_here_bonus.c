/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:30:46 by afanti            #+#    #+#             */
/*   Updated: 2023/03/13 16:46:29 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	t_memcmp(const void *s1, const void *s2)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*d2;

	i = 0;
	d1 = (unsigned char *) s1;
	d2 = (unsigned char *) s2;
	while (d2[i + 1] && d1[i])
	{
		if (d1[i] != d2[i])
			return (d1[i] - d2[i]);
		i++;
	}
	if (d2[i] == '\n' && d1[i] == '\0')
		return (0);
	else
		return (1);
}

void	complit_here(t_data *data, int d, char **av)
{
	data->d = 0;
	data->limiter = get_next_line(0);
	d = t_memcmp(av[2], data->limiter);
	while (d != 0)
	{
		data->here_doc = t_strjoin(data->here_doc, data->limiter);
		free(data->limiter);
		data->limiter = get_next_line(0);
		d = t_memcmp(av[2], data->limiter);
	}
	write (data->pipes[1], data->here_doc, ft_strlen(data->here_doc));
	close(data->pipes[1]);
	dup2(data->pipes[0], STDIN_FILENO);
	dup2(data->pipes[1], STDOUT_FILENO);
}

void	main_next11(t_data *data, char **av)
{
	data->file = open(av[1], O_RDWR, 0777);
	if (data->file < 0)
		error_fd(av[1]);
	dup2(data->file, STDIN_FILENO);
	close(data->pipes[0]);
	dup2(data->pipes[1], STDOUT_FILENO);
}

void	main_next(char **av, char **env, int i, t_data *data)
{
	while (data->av_nbr >= i)
	{
		if (pipe(data->pipes) < 0)
			exit(1);
		data->pid = fork();
		if (data->pid < 0)
			exit(1);
		if (data->pid == 0)
		{
			main_next1(data, av, i);
			main_next2(data, av, env);
		}
		close_pipes(data);
		data->d++;
		i++;
	}
}
