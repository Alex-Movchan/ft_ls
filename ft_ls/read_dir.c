
#include <time.h>
#include "ft_ls.h"

char    *ft_access(struct stat buf)
{
	char    *mod;
	int     i;

	i = 0;
	mod = (char*)malloc(sizeof(char) * 11);
	mod[i] = S_ISFIFO(buf.st_mode) ? 'p' : mod[i];
	mod[i] = S_ISCHR(buf.st_mode) ? 'c' : mod[i];
	mod[i] = S_ISDIR(buf.st_mode) ? 'd' :mod[i];
	mod[i] = S_ISBLK(buf.st_mode) ? 'b' : mod[i];
	mod[i] = S_ISREG(buf.st_mode) ? '-' : mod[i];
	mod[i] = S_ISLNK(buf.st_mode) ? 'l' : mod[i];
	mod[i] = S_ISSOCK(buf.st_mode) ? 's' : mod[i];
	mod[++i] = (buf.st_mode & S_IRUSR) ? 'r' : '-';
	mod[++i] = (buf.st_mode & S_IWUSR) ? 'w' : '-';
	mod[++i] = (buf.st_mode & S_IXUSR) ? 'x' : '-';
	mod[++i] = (buf.st_mode & S_IRGRP) ? 'r' : '-';
	mod[++i] = (buf.st_mode & S_IWGRP) ? 'w' : '-';
	mod[++i] = (buf.st_mode & S_IXGRP) ? 'x' : '-';
	mod[++i] = (buf.st_mode & S_IROTH) ? 'r' : '-';
	mod[++i] = (buf.st_mode & S_IWOTH) ? 'w' : '-';
	mod[++i] = (buf.st_mode & S_IXOTH) ? 'x' : '-';
	mod[++i] = '\0';
	return (mod);
}

void	file_data(struct stat buf, struct dirent *dir, t_file **file, t_arg *arg)
{
	t_file	*lst;

	lst = *file;
	lst->name = ft_strdup(dir->d_name);
	lst->st_nlink = buf.st_nlink;
	lst->access = ft_access(buf);
	lst->pw_name = getpwuid(buf.st_uid)->pw_name;
	lst->gr_name = getgrgid(buf.st_gid)->gr_name;
	lst->st_size = buf.st_size;
	lst->st_time = arg->u == 0 ? buf.st_mtim.tv_sec : buf.st_atim.tv_sec;
}

t_file	*search_last_file(struct stat buf, struct dirent *dir, t_file *file, t_arg *arg)
{
	t_file	*lst;

	if (!file)
	{
		file = (t_file*)malloc(sizeof(t_file));
		lst = file;
	}
	else
	{
		lst = file;
		while (lst->next)
			lst = lst->next;
		lst->next = (t_file*)malloc(sizeof(t_file));
		lst = lst->next;
	}
	lst->next = NULL;
	file_data(buf, dir, &lst, arg);
	return (file);
}

t_file	*read_dir(DIR *ptr, t_arg *arg)
{
	t_file			*file;
	struct dirent	*dir;
	struct stat		buf;

	file = NULL;
	while ((dir = readdir(ptr))&& stat(dir->d_name, &buf) == 0)
	{
		file = search_last_file(buf, dir, file, arg);
	}
	return (file);
}
