/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 23:47:51 by itemlali          #+#    #+#             */
/*   Updated: 2026/05/11 01:31:02 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

int	overflows_int(char *str)
{
	unsigned long long	ullong_arg;

	ullong_arg = 0;
	if (ft_strlen(str) > 10)
		return (TRUE);
	ullong_arg = ft_atoull(str);
	printf(" \n\nint %llu\n\n", ullong_arg);
	if (ullong_arg > INT_MAX)
		return (TRUE);
	return (FALSE);
}

int	overflows_long_long(char *str)
{
	unsigned long long	ullong_arg;

	ullong_arg = 0;
	if (ft_strlen(str) > 19)
		return (TRUE);
	ullong_arg = ft_atoull(str);
	printf("\n\n LLONG %llu\n\n", ullong_arg);
	if (ullong_arg > LLONG_MAX)
		return (TRUE);
	return (FALSE);
}
