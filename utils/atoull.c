/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoull.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 00:06:42 by itemlali          #+#    #+#             */
/*   Updated: 2026/05/10 02:07:31 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

unsigned long long	ft_atoull(const char *nptr)
{
	int					i;
	unsigned long long	result;

	result = 0;
	i = 0;
	while (nptr[i])
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result);
}
