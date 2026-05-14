/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 02:56:48 by itemlali          #+#    #+#             */
/*   Updated: 2026/05/14 03:05:45 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	the_creator(t_data *data)
{
	printf("\ncreator works: %lld\n", (data->config->time_to_compile));
	return ;
}

