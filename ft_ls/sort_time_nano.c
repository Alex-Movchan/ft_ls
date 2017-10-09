/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_time_nano.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 19:45:10 by amovchan          #+#    #+#             */
/*   Updated: 2017/10/09 19:45:54 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_sort_time_alpha(t_file *lst, t_file *file)
{
	while (lst && lst->next && lst->next->st_time == file->st_time &&
			lst->next->st_nano == file->st_nano)
	{
		if (ft_strcmp(lst->next->name, file->name) > 0)
		{
			file->next = lst->next;
			lst->next->previous = file;
			lst->next = file;
			file->previous = lst;
			return ;
		}
		lst = lst->next;
	}
	file->next = lst->next;
	if (lst->next)
		lst->next->previous = file;
	lst->next = file;
	file->previous = lst;
}

void		sort_nano(t_file *lst, t_file *file)
{
	while (lst && lst->next && lst->next->st_time == file->st_time)
	{
		if (lst->next->st_nano < file->st_nano)
		{
			file->next = lst->next;
			lst->next->previous = file;
			lst->next = file;
			file->previous = lst;
			return ;
		}
		else if (lst->next->st_nano == file->st_nano)
			return (ft_sort_time_alpha(lst, file));
		lst = lst->next;
	}
	file->next = lst->next;
	if (lst->next)
		lst->next->previous = file;
	lst->next = file;
	file->previous = lst;
}
