/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_colum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 18:32:37 by amovchan          #+#    #+#             */
/*   Updated: 2017/10/01 18:32:42 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*ft_search_file_rev(t_file *file, int n, int count, int max)
{
	t_file	*lst;

	lst = file;
	n *= (max - count);
	while (lst && n)
	{
		lst = lst->previous;
		n--;
	}
	return (lst);
}

static t_file	*ft_search_file(t_file *file, int n, int count, int max)
{
	t_file	*lst;

	lst = file;
	n *= (max - count);
	while (lst && n)
	{
		lst = lst->next;
		n--;
	}
	return (lst);
}

static int		*init_size(t_file *file)
{
	int		*size;

	size = (int*)malloc(sizeof(int) * 5);
	size[0] = size_colum();
	size[1] = largest_name_len(file);
	size[2] = count_file(file);
	size[3] = size[2] % (size[0] / size[1]) > 0 ? 1 : 0;
	size[3] += size[2] / (size[0] / size[1]);
	return (size);
}

void			print_colum_rev(t_file *file, int i)
{
	int		*size;
	t_file	*lsr;

	size = init_size(file);
	i = size[3];
	last_file(&file);
	while (file && i > 0)
	{
		size[4] = size[0] / size[1];
		while (size[4] > 0)
		{
			if ((lsr = ft_search_file_rev(file,
					size[3], size[4], (size[0] / size[1]))) != NULL)
				lsr->color == NULL ? ft_printf("%-*s", size[1], lsr->name) :
				ft_printf("%s%-*s%s", lsr->color, size[1], lsr->name, EOC);
			size[4]--;
		}
		if (i > 1)
			ft_printf("\n");
		file = file->previous;
		i--;
	}
	ft_printf("\n");
	free(size);
}

void			print_colum(t_file *file, int i)
{
	int		*size;
	t_file	*lsr;

	size = init_size(file);
	i = size[3];
	while (file && i > 0)
	{
		size[4] = size[0] / size[1];
		while (size[4] > 0)
		{
			if ((lsr = ft_search_file(file,
					size[3], size[4], (size[0] / size[1]))) != NULL)
				lsr->color == NULL ? ft_printf("%-*s", size[1], lsr->name) :
				ft_printf("%s%-*s%s", lsr->color, size[1], lsr->name, EOC);
			size[4]--;
		}
		if (i > 1)
			ft_printf("\n");
		file = file->next;
		i--;
	}
	ft_printf("\n");
	free(size);
}
