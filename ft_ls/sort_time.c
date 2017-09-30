
#include "ft_ls.h"

static void	second_nano(t_file **begin, t_file *file)
{
	if ((*begin)->st_nano < file->st_nano ||
			((*begin)->st_nano == file->st_nano && ft_strcmp((*begin)->name, file->name) > 0))
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

static void	second_file_time(t_file **begin, t_file *file)
{
	if ((*begin)->st_time < file->st_time)
	{
		file->next = *begin;
		(*begin)->previous = file;
		*begin = (*begin)->previous;
	}
	else if ((*begin)->st_time == file->st_time)
		second_nano(begin, file);
	else
	{
		(*begin)->next = file;
		file->previous = *begin;
	}
}

static void	sort_nano(t_file **lst, t_file *file)
{
	if ((*lst)->next->st_nano < file->st_nano ||
			((*lst)->next->st_nano == file->st_nano &&
			ft_strcmp((*lst)->next->name, file->name) > 0))
	{
		file->next = (*lst)->next;
		(*lst)->next->previous = file;
		(*lst)->next = file;
		file->previous = *lst;
	}
	else
	{
		(*lst) = (*lst)->next;
		file->next = (*lst)->next;
		if ((*lst)->next)
			(*lst)->next->previous = file;
		(*lst)->next = file;
		file->previous = *lst;
	}
}

static void	ft_find_place_time(t_file **begin, t_file *file)
{
	t_file	*lst;

	lst = *begin;
	while (lst->next)
	{
		if (lst->next->st_time < file->st_time)
		{
			file->next = lst->next;
			lst->next->previous = file;
			lst->next = file;
			file->previous = lst;
			break ;
		}
		else if (lst->next->st_time == file->st_time)
			return(sort_nano(&lst, file));
		lst = lst->next;
	}
	if (lst->next != file)
	{
		lst->next = file;
		file->previous = lst;
	}
}

void		add_time_file(t_file **begin, t_file *file)
{
	if (!(*begin)->next)
		second_file_time(begin, file);
	else if ((*begin)->st_time < file->st_time || ((*begin)->st_time == file->st_time && (*begin)->next->st_nano < file->st_nano) || ((*begin)->next->st_nano == file->st_nano && ft_strcmp((*begin)->next->name, file->name) > 0))
	{
		file->next = *begin;
		(*begin)->previous = file;
		*begin = (*begin)->previous;
	}
	else
		ft_find_place_time(begin, file);
}