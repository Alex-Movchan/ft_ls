
#include "ft_ls.h"

static int		first_arg_time(t_file **file)
{
	t_file	*lst;

	if ((*file)->st_time < (*file)->next->st_time)
	{
		lst = (*file)->next;
		(*file)->next = (*file)->next->next;
		lst->next = (*file);
		(*file) = lst;
		return (0);
	}
	return (1);
}

t_file	*sort_tim(t_file *file)
{
	t_file	*lst;
	t_file	*tmp;
	t_file	*tmp2;

	lst = file;
	while (lst->next->next)
	{
		if (lst->next->st_time < lst->next->next->st_time)
		{
			tmp = lst->next;
			tmp2 = lst->next->next->next;
			lst->next = lst->next->next;
			lst = lst->next;
			lst->next = tmp;
			tmp->next = tmp2;
			lst = file;
		}
		else
			lst = lst->next;
	}
	if (!first_arg_time(&file))
		sort_tim(file);
	return (file);
}
