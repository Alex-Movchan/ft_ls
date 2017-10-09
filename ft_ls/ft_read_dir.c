/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 19:29:58 by amovchan          #+#    #+#             */
/*   Updated: 2017/10/01 19:30:00 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file			*file_data(struct stat buf, t_arg *arg)
{
	t_file	*lst;

	lst = (t_file*)malloc(sizeof(t_file));
	lst->next = NULL;
	lst->previous = NULL;
	lst->st_nlink = buf.st_nlink;
	lst->st_uid = buf.st_uid;
	lst->st_gid = buf.st_gid;
	lst->pw_name = ft_strdup(getpwuid(buf.st_uid)->pw_name);
	lst->gr_name = ft_strdup(getgrgid(buf.st_gid)->gr_name);
	lst->st_size = buf.st_size;
	lst->st_time = arg->u == 0 ?
		buf.st_mtimespec.tv_sec : buf.st_atimespec.tv_sec;
	lst->st_nano = arg->u == 0 ?
		buf.st_mtimespec.tv_nsec : buf.st_atimespec.tv_nsec;
	lst->blok = buf.st_blocks;
	return (lst);
}

static void		ft_without_sorting(t_file **begin, t_file *file)
{
	t_file	*lst;

	lst = *begin;
	if (!ft_strcmp(".", file->name))
	{
		file->next = *begin;
		(*begin)->previous = file;
		*begin = (*begin)->previous;
		return ;
	}
	while (lst->next)
		lst = lst->next;
	lst->next = file;
	file->previous = lst;
}

static void		ft_add_file(t_file **begin, t_file *file, t_arg *arg)
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

static t_file	*init_file(struct dirent dir, struct stat buf,
							t_arg *arg, char *src)
{
	t_file	*file;

	file = file_data(buf, arg);
	file->access = ft_access(buf, src, ft_strnew(11));
	file->name = ft_strdup(dir.d_name);
	file->path = src;
	file->d_name = file->access[0] == 'd' ? ft_strdup(file->name) : NULL;
	file->color = arg->upper_g == 1 ? ft_get_color(file->access) : NULL;
	return (file);
}

void			read_dir(DIR *ptr, t_arg *arg, char *name, t_file **begin)
{
	t_file			*file;
	struct dirent	*dir;
	struct stat		buf;
	char			*src;

	while ((dir = readdir(ptr)) != NULL)
	{
		if (arg->a == 0 && dir->d_name[0] == '.' && arg->d == 0)
			continue ;
		src = name_in_dr(name, dir->d_name);
		if (lstat(src, &buf) == 0)
		{
			file = init_file(*dir, buf, arg, src);
			if (arg->d == 1 && !ft_strcmp(".", file->name))
			{
				ft_dell_file(begin);
				*begin = file;
				return ;
			}
			ft_add_file(begin, file, arg);
		}
	}
}
