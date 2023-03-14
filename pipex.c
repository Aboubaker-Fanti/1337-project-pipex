/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:21:38 by afanti            #+#    #+#             */
/*   Updated: 2023/03/13 19:26:32 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_cmd(char *s)
{
	int	i;

	i = 0;
	write (2, "bash: ", 6);
	while (s[i])
		write (2, &s[i++], 1);
	if (s[0] == '\0')
		write (2, ": permission denied:\n", 22);
	else if (s[0] == '/')
		write (2, ": No such file or directory\n", 28);
	else if (s[0] != '/')
		write (2, ": command not found\n", 20);
	exit (127);
}

void	error_fd(char *s)
{
	int		i;
	char	*str;

	i = 0;
	write (2, "bash: ", 6);
	while (s[i])
		write (2, &s[i++], 1);
	write (2, ": ", 2);
	i = 0;
	str = strerror(errno);
	while (str[i])
		write (2, &str[i++], 1);
	write (2, "\n", 1);
	exit (1);
}

void	while_here(char **av, t_data *data, char **env, int i)
{
	while (i < 2)
	{
		data->pid[i] = fork();
		if (data->pid < 0)
			exit(1);
		if (data->pid[i] == 0 && i == 0)
		{
			execute_one(av, data, env);
			last_execute(data, env);
			error_cmd(data->cmd[0]);
		}
		else if (data->pid[i] == 0 && i == 1)
		{
			execute_two(av, data, env);
			last_execute1(data, env);
			error_cmd(data->cmd1[0]);
		}
		i++;
	}
}

void	last_execute1(t_data *data, char **env)
{	
	while (data->spliti[data->i])
	{
		if (data->cmd1[0][0] == '/')
			error_cmd(data->cmd1[0]);
		data->comman = ft_strjoin(data->spliti[data->i], "/");
		data->comman = ft_strjoin(data->comman, data->cmd1[0]);
		if (access(data->comman, X_OK) != -1)
		{
			dup2(data->fd1, STDOUT_FILENO);
			execve(data->comman, data->cmd1, env);
		}
		free(data->comman);
		data->i++;
	}
}

int	main(int ac, char **av, char **env)
{
	int		i;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->i = 0;
	i = 0;
	if (ac == 5)
	{
		data->fd1 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (data->fd1 < 0)
			error_fd(av[4]);
		if (pipe(data->pip) < 0)
			exit(1);
		while_here(av, data, env, i);
		close(data->pip[1]);
		close(data->pip[0]);
		waitpid(data->pid[1], NULL, 0);
		waitpid(data->pid[0], NULL, 0);
	}
	if (ac != 5)
		write (2, "should be like this: ./pipex infile cmd1 cmd2 outfile\n", 54);
}
