/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_par.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanti <afanti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 08:50:18 by afanti            #+#    #+#             */
/*   Updated: 2023/03/11 12:17:22 by afanti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_av(char *str)
{
	int	d;
	int	i;

	i = 0;
	d = 0;
	if (str[i] == '\0')
		error_cmd("");
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
			error_cmd("");
	}
}
