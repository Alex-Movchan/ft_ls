/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 19:52:44 by amovchan          #+#    #+#             */
/*   Updated: 2017/10/01 19:52:54 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_ls(t_file *file, t_arg *arg, int *max)
{
	char	*time;

	time = ft_strndup((ctime(&file->st_time) + 4), 12);
	time[12] = '\0';
	if (arg->upper_g)
		file->name = name_color(file->name, file->access);
	if (arg->l == 1)
		ft_printf("%s% *d %-*s %-*s% *d %s %s\n", file->access,
		max[0], file->st_nlink, max[2], file->pw_name, max[3],
		file->gr_name, max[1], file->st_size, time, file->name);
	else if (arg->g == 1)
		ft_printf("%s% *d %-*s% *d %s %s\n", file->access,
			max[0], file->st_nlink, max[3], file->gr_name, max[1],
			file->st_size, time, file->name);
	else if (arg->n == 1)
		ft_printf("%s% *d %-*d %-*d% *d %s %s\n", file->access, max[0],
			file->st_nlink, max[5], file->st_uid, max[4], file->st_gid,
			max[1], file->st_size, time, file->name);
	ft_strdel(&time);
}

static void	print_one(t_file *file, t_arg *arg)
{
	if (arg->r)
	{
		while (file)
		{
			file->color == NULL ? ft_printf("%s\n", file->name) :
			ft_printf("%s%s%s\n", file->color, file->name, EOC);
			file = file->previous;
		}
		return ;
	}
	while (file)
	{
		file->color == NULL ? ft_printf("%s\n", file->name) :
		ft_printf("%s%s%s\n", file->color, file->name, EOC);
		file = file->next;
	}
}

static void	print_revers(t_file *file, t_arg *arg)
{
	int		*max;

	if (arg->g == 0 && arg->l == 0 && arg->one == 0 && arg->n == 0)
		return (print_colum_rev(file, 0));
	last_file(&file);
	if (arg->one == 1)
		return (print_one(file, arg));
	if (arg->l || arg->g || arg->n)
	{
		ft_printf("total %d\n", ft_total(file, arg));
		max = largestelem(file, arg);
		while (file)
		{
			print_ls(file, arg, max);
			file = file->previous;
		}
		free(max);
	}
}

void		print_file(t_file *file, t_arg *arg)
{
	int		*max;

	if (arg->r)
		return (print_revers(file, arg));
	if (arg->g == 0 && arg->l == 0 && arg->one == 0 && arg->n == 0)
		return (print_colum(file, 0));
	if (arg->one == 1)
		return (print_one(file, arg));
	if (arg->l || arg->g || arg->n)
	{
		if (arg->n == 0)
			ft_printf("total %d\n", ft_total(file, arg));
		max = largestelem(file, arg);
		while (file)
		{
			print_ls(file, arg, max);
			file = file->next;
		}
		free(max);
	}
}
