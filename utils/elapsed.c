/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elapsed.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:11:30 by itemlali          #+#    #+#             */
/*   Updated: 2026/08/04 11:14:23 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

long elapsed(t_data* data)
{
    return (current_time() - data->start_time);
}
