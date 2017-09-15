
#include "ft_ls.h"

static void	print_file(t_file *file, t_arg *arg)
{
	if (arg->l)
	{
		while (file)
		{
			if (arg->a == 0 && file->name[0] == '.')
			{
				file = file->next;
				continue;
			}
			ft_printf("%s %d %s %s % 6d %d %s\n", file->access, file->st_nlink, file->pw_name, file->gr_name,
					  file->st_size, file->st_time, file->name);
			file = file->next;
		}
	}
}
static void	print_revers(t_file *file, t_arg *arg)
{
	previous_communication(&file);
	last_file(&file);
	if (arg->l)
	{
		while (file->previous)
		{
			if (arg->a == 0 && file->name[0] == '.')
			{
				file = file->previous;
				continue ;
			}
			ft_printf("%s %d %s %s % 6d %d %s\n", file->access, file->st_nlink, file->pw_name, file->gr_name, file->st_size, file->st_time, file->name);
			file = file->previous;
		}
	}
}

void    	ft_ls(t_arg *arg)
{
    DIR *ptr;
	t_file	*file;

	ptr = opendir(".");
	file = read_dir(ptr, arg);
	file= sort_alpha(file);
	if (arg->t || arg->u)
		file = sort_tim(file);
	if (arg->r)
		print_revers(file, arg);
	else
		print_file(file, arg);

}