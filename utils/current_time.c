/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:55:58 by itemlali          #+#    #+#             */
/*   Updated: 2026/08/01 18:10:09 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (TRUE);
	return (FALSE);
}

long	current_time(void)
{
	struct timeval	startime;
	long			startime_in_ms;

	gettimeofday(&startime, NULL);
	startime_in_ms = startime.tv_sec * 1000 + startime.tv_usec / 1000;
	return (startime_in_ms);
}
