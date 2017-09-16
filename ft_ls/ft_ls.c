
#include "ft_ls.h"

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

static void	print_file(t_file *file, t_arg *arg)
{
	if (arg->l)
		ft_printf("total %d\n", ft_total(file, arg));
		while (file)
		{
			if (arg->a == 0 && file->name[0] == '.')
			{
				file = file->next;
				continue;
			}
			if (arg->l)
				ft_printf("%s %d %s %s % 6d %d %s\n", file->access, file->st_nlink, file->pw_name, file->gr_name,
					  file->st_size, file->st_time, file->name);
			else if (arg->one)
				ft_printf("%s\n", file->name);
			file = file->next;
		}
}
static void	print_revers(t_file *file, t_arg *arg)
{
	if (arg->l)
		ft_printf("total %d\n", ft_total(file, arg));
	previous_communication(&file);
	last_file(&file);
	while (file->previous)
	{
		if (arg->a == 0 && file->name[0] == '.')
		{
			file = file->previous;
			continue;
		}
		if (arg->l)
			ft_printf("%s %d %s %s % 6d %d %s\n", file->access, file->st_nlink, file->pw_name, file->gr_name,
					  file->st_size, file->st_time, file->name);
		else if (arg->one)
			ft_printf("%s\n", file->name);
		file = file->previous;
	}
}

void    	ft_ls(t_arg *arg, char *name) {
	DIR *ptr;
	t_file *file;

	if (!(ptr = opendir(name)))
	{
		ft_printf("%{fd}s\n", 2, "Error opening");
		return ;
	}
	if (!(file = read_dir(ptr, arg, name)))
	{
		ft_printf("%{fd}s\n", 2, "Error reading");
		closedir(ptr);
		return ;
	}
	closedir(ptr);
	file = sort_alpha(file);
	if (arg->t || arg->u)
		file = sort_tim(file);
	if (arg->r)
		print_revers(file, arg);
	else
		print_file(file, arg);

}