/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 17:04:15 by nschilli          #+#    #+#             */
/*   Updated: 2026/09/25 18:09:39 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (48 <= c && c <= 57)
			return (1);
	return (0);
}

/*
	only returns positive long if the argument is invalid it returns -1
*/
long	pos_long_atoi(char *str)
{
		int			i;
		long long	out;

		i = 0;
		out = 0;
		while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
				i++;
		if (str[i] == '+')
				i++;
		if (str[i] == '-')
			return (-1);
		while (ft_isdigit(str[i]))
		{
				out = out * 10 + (str[i] - 48);
				if (out > LONG_MAX)
					return (-1);
				i++;
		}
		return ((long) out);
}
int	pos_int_atoi(char *str)
{
	long	tmp;

	tmp = pos_long_atoi(str);
	if (tmp > LONG_MAX || tmp  == -1)
		return (-1);
	return ((int) tmp);
}