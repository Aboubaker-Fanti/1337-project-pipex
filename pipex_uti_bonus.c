/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_uti_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:51:54 by afanti            #+#    #+#             */
/*   Updated: 2023/03/12 19:26:03 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*d2;

	i = 0;
	d1 = (unsigned char *) s1;
	d2 = (unsigned char *) s2;
	while (i < n)
	{
		if (d1[i] != d2[i])
		{
			return (d1[i] - d2[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
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
	free(s1);
	return (str);
}

void	error_cmd(char *s)
{
	int	i;

	i = 0;
	write (2, "bash: ", 6);
	while (s[i])
		write (2, &s[i++], 1);
	if (s[0] == ' ')
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

void	check_av(char *str)
{
	int	d;
	int	i;

	i = 0;
	d = 0;
	if (str[i] == '\0')
		error_cmd(" ");
	else if (str[i] == ' ')
	{
		while (str[i])
		{
			if (str[i] == ' ')
				i++;
			else
				break ;
		}
		while (str[d])
			d++;
		if (i == d)
			error_cmd(" ");
	}
}
