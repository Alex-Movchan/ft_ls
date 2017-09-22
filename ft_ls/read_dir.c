
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
	lst->st_time = arg->u == 0 ? buf.st_mtim.tv_sec : buf.st_atim.tv_sec;//Linux
	lst->st_nano = arg->u == 0 ? buf.st_mtim.tv_nsec : buf.st_atim.tv_nsec;
//	lst->st_time = arg->u == 0 ? buf.st_mtimespec.tv_sec : buf.st_atimespec.tv_sec;
	lst->blok = buf.st_blocks;
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

char	*name_in_dr(char *name, char *file)
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

t_file	*read_dir(DIR *ptr, t_arg *arg, char *name)
{
	t_file			*file;
	struct dirent	*dir;
	struct stat		buf;
	char			*src;

	file = NULL;
	while ((dir = readdir(ptr)) != NULL)
	{
		src = name_in_dr(name, dir->d_name);
		if (lstat(src, &buf) == 0)
			file = search_last_file(buf, dir, file, arg);
		ft_strdel(&src);
	}
	return (file);
}
