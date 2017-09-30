#include "ft_ls.h"

void	last_file(t_file **file)
{
	while ((*file)->next)
		(*file) = (*file)->next;
}

int		*largestelem(t_file *file)
{
	int		*max;
	t_file	*lst;

	lst = file;
	max = (int*)malloc(sizeof(int) * 4);
	max[0] = 0;
	max[1] = 0;
	max[2] = 0;
	max[3] = 0;
	while (lst)
	{
		if (max[0] < ft_len_int((int)lst->st_nlink))
			max[0] = ft_len_int((int)lst->st_nlink);
		if (max[1] < ft_len_int((int)lst->st_size))
			max[1] = ft_len_int((int)lst->st_size);
		if (max[2] < ft_strlen(lst->pw_name))
			max[2] = (int)ft_strlen(lst->pw_name);
		if (max[3] < ft_strlen(lst->gr_name))
			max[3] = (int)ft_strlen(lst->gr_name);
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
	return (res);
}
