/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tail.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnohara <hnohara@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 08:47:00 by hnohara           #+#    #+#             */
/*   Updated: 2020/09/30 17:34:59 by hnohara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int		g_buf_size;
char	*g_buf;
char	*g_prog_name;

void	print_error(char *fname)
{
	print(basename(g_prog_name));
	print(": ");
	print(fname);
	print(": ");
	print(strerror(errno));
	print("\n");
}

void	display_file_by_size(char *fname, int file_size)
{
	int i;
	int j;
	int fd;

	i = 0;
	j = 0;
	if ((fd = open(fname, O_RDONLY)) == -1)
	{
		print_error(fname);
		return ;
	}
	while (read(fd, &g_buf[j], 1))
	{
		if (file_size <= g_buf_size || i + g_buf_size >= file_size)
		{
			j++;
			continue ;
		}
		i++;
	}
	close(fd);
	write(1, g_buf, g_buf_size);
}


void	ft_display_file(int fd, char *fname)
{
	int file_size;
	
	file_size = 0;
	if (g_buf_size == 0)
	{
		while (read(fd, g_buf, 1))
			if (errno != 0)
				return ;
		return ;
	}
	while (read(fd, g_buf, 1))
	{
		if (errno != 0)
				return ;
			file_size++;
	}
	close(fd);
	display_file_by_size(fname, file_size);
}

void	ft_manage_display(int argc, char *argv[])
{
	int i;
	int is_first_print;
	int fd;

	i = 2;
	is_first_print = 1;
	while (++i < argc)
	{
		errno = 0;
		if ((fd = open(argv[i], O_RDONLY)) == -1)
		{
			print_error(argv[i]);
			continue ;
		}
		if (argc > 4)
		{
			if (!is_first_print)
				print("\n");
			print("==> ");
			print(argv[i]);
			print(" <==\n");
		}
		is_first_print = 0;
		ft_display_file(fd, argv[i]);
	}
}

int		main(int argc, char *argv[])
{
	g_prog_name = argv[0];
	g_buf_size = to_number(argv[2]);
	g_buf = (char *)malloc(sizeof(char) * g_buf_size);
	if (argc == 3)
		ft_display_file(0, "");
	else
		ft_manage_display(argc, argv);
	free(g_buf);
	return (0);
}
