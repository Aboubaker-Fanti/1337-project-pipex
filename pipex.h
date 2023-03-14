/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:26:59 by afanti            #+#    #+#             */
/*   Updated: 2023/03/13 11:53:36 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/fcntl.h>
# include <string.h>
# include <errno.h>
# include "get_next_line/get_next_line.h"

typedef struct t_datta{
	int		pid[2];
	int		i;
	int		fd;
	int		fd1;
	char	**cmd;
	char	*command;
	char	*path;
	char	**cmd1;
	int		d;
	char	*comman;
	char	*pathh;
	char	**spliti;
	char	**splitit;
	int		pip[2];
}				t_data;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	execute_one(char **av, t_data *data, char **env);
void	execute_two(char **av, t_data *data, char **env);
void	last_execute(t_data *data, char **env);
void	last_execute1(t_data *data, char **env);
void	check_av(char *str);
void	error_cmd(char *s);
void	error_fd(char *s);

#endif
