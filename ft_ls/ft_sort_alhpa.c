/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_alhpa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 19:31:56 by amovchan          #+#    #+#             */
/*   Updated: 2017/10/01 19:32:02 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	second_file(t_file **begin, t_file *file)
{
	if (ft_strcmp((*begin)->name, file->name) > 0)
	{
		file->next = *begin;
		(*begin)->previous = file;
		*begin = (*begin)->previous;
	}
	else
	{
		(*begin)->next = file;
		file->previous = *begin;
	}
}

static void	ft_find_place(t_file **begin, t_file *file)
{
	t_file	*lst;

	lst = *begin;
	while (lst && lst->next)
	{
		if (ft_strcmp(lst->next->name, file->name) > 0)
		{
			file->next = lst->next;
			lst->next->previous = file;
			lst->next = file;
			file->previous = lst;
			break ;
		}
		lst = lst->next;
	}
	if (lst->next != file)
	{
		lst->next = file;
		file->previous = lst;
	}
}

void		add_alpha_file(t_file **begin, t_file *file)
{
	if (!(*begin)->next)
		second_file(begin, file);
	else if (ft_strcmp((*begin)->name, file->name) > 0)
	{
		file->next = *begin;
		(*begin)->previous = file;
		*begin = (*begin)->previous;
	}
	else
		ft_find_place(begin, file);
}
