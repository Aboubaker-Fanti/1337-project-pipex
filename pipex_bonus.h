/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:42:28 by afanti            #+#    #+#             */
/*   Updated: 2023/03/13 16:47:42 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/fcntl.h>
# include <string.h>
# include <errno.h>
# include "get_next_line/get_next_line.h"

typedef struct t_datta {
	int		i;
	int		d;
	int		c;
	int		av_nbr;
	int		file;
	int		pipes[2];
	int		pipes1[2];
	int		pid;
	char	**av2afslt;
	char	**av_x;
	char	*path;
	char	*path_x;
	char	**path2d;
	char	**path2d_x;
	char	*command;
	char	*command_x;
	int		fd_stdout;
	int		here;
	char	*here_doc;
	char	*limiter;
}				t_data;

char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	while_here(t_data *data, char **av, char **env);
void	error_cmd(char *s);
void	error_fd(char *s);
void	check_av(char *str);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	complit_here(t_data *data, int d, char **av);
void	main_next11(t_data *data, char **av);
void	main_next(char **av, char **env, int i, t_data *data);
void	main_next2(t_data *data, char **av, char **env);
void	main_next1(t_data *data, char **av, int i);
void	close_pipes(t_data *data);

#endif
