
#include "ft_ls.h"

void	previous_communication(t_file **file)
{
	t_file	*lst;

	(*file)->previous = NULL;
	lst = *file;
	while (lst->next)
	{
		lst->next->previous = lst;
		lst = lst->next;
	}
}

void	last_file(t_file **file)
{
	while ((*file)->next)
		(*file) = (*file)->next;
}