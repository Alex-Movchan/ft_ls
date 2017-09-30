#include "ft_ls.h"

static t_file	*file_data(struct stat buf, struct dirent *dir, t_arg *arg)
{
	t_file	*lst;

	lst = (t_file*)malloc(sizeof(t_file));
	lst->next = NULL;
	lst->previous = NULL;
	lst->st_nlink = buf.st_nlink;
	lst->pw_name = ft_strdup(getpwuid(buf.st_uid)->pw_name);
	lst->gr_name = ft_strdup(getgrgid(buf.st_gid)->gr_name);
	lst->st_size = buf.st_size;
	lst->st_time = arg->u == 0 ? buf.st_mtimespec.tv_sec : buf.st_atimespec.tv_sec;
	lst->st_nano = arg->u == 0 ? buf.st_mtimespec.tv_nsec : buf.st_atimespec.tv_nsec;
	lst->blok = buf.st_blocks;
	return (lst);
}

static char	*name_in_dr(char *name, char *file)
{
	char	*tab;
	char	*s;

	if (name[0] == '.' && name[1] == '\0')
		return (ft_strdup(file));
	if (name[ft_strlen(name) - 1] != '/')
		tab = ft_strjoin(name, "/");
	else
		tab = ft_strdup(name);
	s = ft_strjoin(tab, file);
	ft_strdel(&tab);
	return (s);
}

static void	ft_without_sorting(t_file **begin, t_file *file)
{
	t_file	*lst;

	lst = *begin;
	if (!ft_strcmp(".", file->name))
	{
		file->next = *begin;
		(*begin)->previous = file;
		*begin = (*begin)->previous;
		return;
	}
	while (lst->next)
		lst = lst->next;
	lst->next = file;
	file->previous = lst;
}

static void ft_add_file(t_file **begin, t_file *file, t_arg *arg)
{
	if (!*begin)
		*begin = file;
	else if (arg->t == 1)
		add_time_file(begin, file);
	else if (arg->f == 1)
		ft_without_sorting(begin, file);
	else
		add_alpha_file(begin, file);
}

void	read_dir(DIR *ptr, t_arg *arg, char *name, t_file **begin)
{
	t_file			*file;
	struct dirent	*dir;
	struct stat		buf;
	char			*src;

	while ((dir = readdir(ptr)) != NULL)
	{
		if (arg->a == 0 && dir->d_name[0] == '.')
			continue ;
		src = name_in_dr(name, dir->d_name);
		if (lstat(src, &buf) == 0)
		{
			file = file_data(buf, dir, arg);
			file->access = ft_access(buf, src);
			file->name = file_name_and_links(src, file->access[0], dir->d_name, arg);
			ft_add_file(begin, file, arg);
		}
		ft_strdel(&src);
	}
}
