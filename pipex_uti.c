/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_uti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:29:16 by afanti            #+#    #+#             */
/*   Updated: 2023/03/13 16:24:52 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s;
	char	*str;

	s = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[s])
	{
		str[i++] = s2[s++];
	}
	str[i] = '\0';
	free((char *)s1);
	return (str);
}

void	execute_one(char **av, t_data *data, char **env)
{
	data->cmd = ft_split(av[2], ' ');
	check_av(av[2]);
	data->fd = open (av[1], O_RDONLY, 0777);
	if (data->fd < 0)
		error_fd(av[1]);
	dup2(data->fd, STDIN_FILENO);
	close(data->pip[0]);
	dup2(data->pip[1], STDOUT_FILENO);
	close(data->pip[1]);
	if (access(data->cmd[0], X_OK) == 0)
		execve(data->cmd[0], data->cmd, env);
	while (env[data->i])
	{
		if (env[data->i][0] == 'P' && env[data->i][3] == 'H')
			data->path = env[data->i];
		data->i++;
	}
	if (data->path == NULL)
		error_cmd(av[2]);
	data->splitit = ft_split(data->path + 5, ':');
	data->i = 0;
}

void	execute_two(char **av, t_data *data, char **env)
{
	check_av(av[3]);
	data->cmd1 = ft_split(av[3], ' ');
	close(data->pip[1]);
	dup2(data->pip[0], STDIN_FILENO);
	data->i = 0;
	if (access(data->cmd1[0], X_OK) == 0)
	{
		dup2(data->fd1, STDOUT_FILENO);
		execve(data->cmd1[0], data->cmd1, env);
	}
	while (env[data->i])
	{
		if (env[data->i][0] == 'P' && env[data->i][3] == 'H')
			data->pathh = env[data->i];
		data->i++;
	}
	if (data->pathh == NULL)
		error_cmd(av[3]);
	data->spliti = ft_split(data->pathh + 5, ':');
	data->i = 0;
}

void	last_execute(t_data *data, char **env)
{
	while (data->splitit[data->i])
	{
		if (data->cmd[0][0] == '/')
			error_cmd(data->cmd[0]);
		data->command = ft_strjoin(data->splitit[data->i], "/");
		data->command = ft_strjoin(data->command, data->cmd[0]);
		if (access(data->command, X_OK) != -1)
			execve(data->command, data->cmd, env);
		free(data->command);
		data->i++;
	}
}
