
#include "ft_ls.h"

static void		print_not_arg(t_file *file, t_arg *arg)
{
	while (file)
	{
		if (arg->a == 0 && file->name[0] == '.')
		{
			file = file->next;
			continue ;
		}
		if (file->access[0] == 'd')
			ft_printf("%{green}s{eoc}  ", file->name);
		else if (file->access[0] == 'l')
			ft_printf("%{bleu}s{eoc}  ", file->name);
		else
		ft_printf("%s  ", file->name);
		file = file->next;
	}
	ft_printf("\n");
}


static void	print_ls2(t_file *file, t_arg *arg, int *max)
{
	char	*time;

	if (arg->g)
	{
		time = ft_strndup((ctime(&file->st_time) + 4), 12);
		if (file->access[0] == 'd')
			ft_printf("%s% *d %s% *d %s %{green}s{eoc}\n", file->access, max[0], file->st_nlink, file->gr_name,
					  max[1], file->st_size, time, file->name);
		else
			ft_printf("%s% *d %s% *d %s %s\n", file->access, max[0], file->st_nlink, file->gr_name,
					  max[1], file->st_size, time, file->name);
		ft_strdel(&time);
	}
}

static void	print_ls(t_file *file, t_arg *arg, int *max)
{
	char	*time;

	if (arg->l)
	{
		time = ft_strndup((ctime(&file->st_time) + 4), 12);
		time[12] = '\0';
		if (file->access[0] == 'd')
			ft_printf("%s% *d %-*s %-*s% *d %s %{green}s{eoc}\n", file->access, max[0], file->st_nlink, max[2], file->pw_name, max[3], file->gr_name,
					max[1], file->st_size, time, file->name);
		else if (file->access[0] == 'l')
			ft_printf("%s% *d %-*s %-*s% *d %s %{bleu}s{eoc}\n", file->access, max[0], file->st_nlink, max[2], file->pw_name, max[3], file->gr_name,
					  max[1], file->st_size, time, file->name);
		else
			ft_printf("%s% *d %-*s %-*s% *d %s %s\n", file->access, max[0], file->st_nlink, max[2], file->pw_name, max[3], file->gr_name,
					 max[1], file->st_size, time, file->name);
		ft_strdel(&time);
	}
	else if (arg->one)
		ft_printf("%s\n", file->name);
	else
		print_ls2(file, arg, max);
}

void		print_file(t_file *file, t_arg *arg)
{
	int		*max;

	if (arg->l)
		ft_printf("total %d\n", ft_total(file, arg));
	max = largestelem(file);
	if (arg->upper_c)
		return (print_colum(file, arg));
	else if (arg->g == 0 && arg->l == 0 && arg->upper_c == 0 && arg->f == 0)
		return (print_not_arg(file, arg));
	while (file)
	{
		if (arg->a == 0 && file->name[0] == '.')
		{
			file = file->next;
			continue;
		}
		print_ls(file, arg, max);
		file = file->next;
	}
	free(max);
}
void		print_revers(t_file *file, t_arg *arg)
{
	char	*time;
	int		*max;

	if (arg->l)
		ft_printf("total %d\n", ft_total(file, arg));
	max = largestelem(file);
	previous_communication(&file);
	last_file(&file);
	while (file->previous)
	{
		if (arg->a == 0 && file->name[0] == '.')
		{
			file = file->previous;
			continue;
		}
		print_ls(file, arg, max);
		file = file->previous;
	}
}
