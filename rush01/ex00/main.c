/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaida <gaida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 16:08:26 by gaida             #+#    #+#             */
/*   Updated: 2020/09/20 17:01:29 by hnohara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "is_input_valid.h"
#include "get_input_arr.h"
#include "store_line_patterns.h"
#include "get_one_pattern.h"
#include "is_unique_num.h"
#include "is_correct.h"
#include "print_correct.h"

bool	inner(int input_arr[], int pattern[][4], int c_all)
{
	int		i;
	bool	is_ok;

	i = 0;
	while (i < c_all)
	{
		get_one_pattern(i, pattern);
		is_ok = is_unique_num(pattern);
		if (!is_ok)
		{
			i++;
			continue ;
		}
		is_ok = is_correct(pattern, input_arr);
		if (is_ok)
			return (true);
		i++;
	}
	return (false);
}

int		main(int argc, char *argv[])
{
	const int	c_all = 24 * 24 * 24 * 24;
	int			input_arr[16];
	bool		is_ok;
	int			pattern[4][4];

	if (argc != 2 || !is_input_valid(argv[1]))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	get_input_arr(argv[1], input_arr);
	store_line_patterns();
	is_ok = inner(input_arr, pattern, c_all);
	if (is_ok)
		print_correct(pattern);
	else
		write(1, "Error\n", 6);
	return (0);
}
