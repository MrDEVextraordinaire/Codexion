/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 23:47:51 by itemlali          #+#    #+#             */
/*   Updated: 2026/05/10 01:57:38 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

int	overflows_int(char *str)
{
	unsigned long long	ullong_arg;

	ullong_arg = 0;
	if (ft_strlen(str) > 10)
		return (1);
	ullong_arg = ft_atoull(str);
	if (ullong_arg > INT_MAX)
		return (1);
	return (0);
}

int	overflows_long_long(char *str)
{
	unsigned long long	ullong_arg;

	ullong_arg = 0;
	if (ft_strlen(str) > 19)
		return (1);
	ullong_arg = ft_atoull(str);
	if (ullong_arg > LLONG_MAX)
		return (1);
	return (0);
}

