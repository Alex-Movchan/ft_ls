
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

int		*largestelem(t_file *file)
{
	int		*max;
	t_file	*lst;
	int		len1;
	int 	len2;

	lst = file;
	max = (int*)malloc(sizeof(int) * 2);
	max[0] = 0;
	max[1] = 0;
	while (lst)
	{
		if (max[0] < (len1 = ft_len_int((int)lst->st_nlink)))
			max[0] = len1;
		if (max[1] < (len2 = ft_len_int((int)lst->st_size)))
			max[1] = len2;
		lst = lst->next;
	}
	max[0]++;
	max[1]++;
	return (max);
}

int		ft_total(t_file *file, t_arg *arg)
{
	int		res;

	res = 0;
	while (file)
	{
		if (arg->a == 0 && file->name[0] == '.')
		{
			file = file->next;
			continue ;
		}
		res += file->blok;
		file = file->next;
	}
	return (res / 2);//linux
}
