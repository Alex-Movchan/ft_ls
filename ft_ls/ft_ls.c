
#include "ft_ls.h"




static void	ft_dell_file(t_file **file)
{
	t_file	*leaks;
	t_file	*lst;

	lst = *file;
	while (lst)
	{
		leaks = lst;
		lst = lst->next;
		if (lst && lst->next)
			lst->previous = NULL;
		ft_strdel(&(leaks->access));
		ft_strdel((&(leaks->name)));
		free(leaks);
	}
}

static void	ft_recursoin(t_file *file, t_arg *arg, char *name)
{
	t_file	*lst;
	char	*src;

	lst = file;
	while (lst)
	{
		if (lst->access[0] == 'd' && ft_strcmp(".", lst->name) &&
				ft_strcmp("..", lst->name) && !(arg->a == 0 && lst->name[0] == '.'))
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
	if (arg->upper_r)
		ft_printf("%s:\n", name);
	if (arg->t || arg->u)
		file = sort_tim(file);
	else
		file = sort_alpha(file);
	if (arg->r)
		print_revers(file, arg);
	else
		print_file(file, arg);
	if (arg->upper_r)
		ft_recursoin(file, arg, name);
	ft_dell_file(&file);

}
