
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
	return (res / 2);//linux
}

static void	print_file(t_file *file, t_arg *arg)
{
	char	*time;

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
			{
				time = ft_strndup((ctime(&file->st_time) + 4), 12);
				if (file->access[0] == 'd')
				ft_printf("%s %d %s %s % 6d %s %{bleu}s{eoc}\n", file->access, file->st_nlink, file->pw_name, file->gr_name,
						  file->st_size, time, file->name);
				else
					ft_printf("%s %d %s %s % 6d %s %s\n", file->access, file->st_nlink, file->pw_name, file->gr_name,
							  file->st_size, time, file->name);
				ft_strdel(&time);
			}
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

void		ft_dell_file(t_file **file)
{
	t_file	*leaks;
	t_file	*lst;

	lst = *file;
	while (lst)
	{
		leaks = lst;
		lst = lst->next;
		lst->previous = NULL;
		ft_strdel(&(leaks->access));
		ft_strdel((&(leaks->name)));
	}
}

void    	ft_ls(t_arg *arg, char *name)
{
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
	if (arg->upper_r)
		ft_printf("%s:\n", name);
	if (arg->t || arg->u)
		file = sort_tim(file);
	if (arg->r)
		print_revers(file, arg);
	else
		print_file(file, arg);
	if (arg->upper_r)
		ft_recursoin(file, arg, name);
	ft_dell_file(&file);

}

void	ft_recursoin(t_file *file, t_arg *arg, char *name)
{
	t_file	*lst;
	char	*src;

	lst = file;
	while (lst)
	{
		if (lst->access[0] == 'd' && ft_strcmp(".", lst->name) && ft_strcmp("..", lst->name) && !(arg->a == 0 && lst->name[0] == '.'))
		{
			if (name[ft_strlen(name) -1] != '/')
				src = ft_strjoin(ft_strjoin(name, "/"), lst->name);
			else
				src = ft_strjoin(name, lst->name);
			ft_ls(arg, src);
			ft_strdel(&src);
		}
		lst = lst->next;
	}
}