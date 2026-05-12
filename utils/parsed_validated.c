/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_validated.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma`       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:55:40 by itemlali          #+#    #+#             */
/*   Updated: 2026/05/09 23:55:14 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

static int	validate_refactor_time(char *argv)
{
	if (ft_atoull(argv) < 1)
	{
		fprintf(stderr, "[Error] time to refactor has to be more than 0\n");
		return (FALSE);
	}
	return (TRUE);
}

static int	validate_scheduler(char *argv)
{
	if ((strcmp(argv, "fifo") == 0))
	{
		printf("argv[8]: %s", argv);
	}
	else if (((strcmp(argv, "edf")) == 0))
	{
		printf("\n8th argument  edf \n");
	}
	else
	{
		fprintf(stderr, "[Error] 8th arg has to be fifo or edf\n");
		return (FALSE);
	}
	return (TRUE);
}

static int	all_ints(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < (argc - 1) && argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				fprintf(stderr, "\n[Error] args must be positive integers\n");
				return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

static int	overflow(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < (argc - 1))
	{
		if (i == 1 || i == 6)
		{
			if (overflows_int(argv[i]))
			{
				fprintf(stderr, "[Error] args 1 or 6 exceed INT_MAX\n");
				return (TRUE);
			}
		}
		else if (overflows_long_long(argv[i]))
		{
			fprintf(stderr, "[Error] a time arg exceeds LLONG_MAX\n");
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	parsed_validated(int argc, char **argv)
{
	if (argc != EXPECTED_ARGS)
	{
		fprintf(stderr, "[Error] Please input 8 valid arguments\n");
		return (FALSE);
	}
	if (!all_ints(argc, argv))
		return (FALSE);
	if (overflow(argc, argv))
		return (FALSE);
	if (atoi(argv[NUMBER_OF_CODERS_ARG]) < 1)
	{
		fprintf(stderr, "\n[Error] you must have at least one coder\n");
		return (FALSE);
	}
	if (!validate_refactor_time(argv[5]))
		return (FALSE);
	if (!validate_scheduler(argv[8]))
		return (FALSE);
	return (TRUE);
}
