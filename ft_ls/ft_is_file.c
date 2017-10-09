/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 18:54:06 by amovchan          #+#    #+#             */
/*   Updated: 2017/10/02 18:54:09 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*ft_search_d_name(char **name)
{
	char	*src;
	char	*d_name;
	int		i;

	i = (int)ft_strlen(*name);
	while (--i >= 0)
	{
		if ((*name)[i] == '/')
			break ;
	}
	i++;
	if (i == 1)
		return (NULL);
	d_name = ft_strndup((*name), (size_t)i);
	src = ft_strdup((*name) + i);
	ft_strdel(name);
	*name = src;
	return (d_name);
}

static int	search_ifo_file(char *path, struct dirent dir, t_arg *arg)
{
	struct stat buf;
	t_file		*file;

	if (lstat(path, &buf) == 0)
	{
		file = file_data(buf, arg);
		file->access = ft_access(buf, path, ft_strnew(11));
		file->name = ft_strdup(dir.d_name);
		file->d_name = NULL;
		file->path = ft_strdup(path);
		file->color = arg->upper_g == 1 ? ft_get_color(file->access) : NULL;
		if (arg->upper_g || arg->g || arg->l || arg->n)
			file->name = file_name_and_links(path,
					file->access, file->name, arg);
		if (file->access[0] == 'd')
			ft_printf("{fd}ft_ls: %{fd}s{fd}: Permission denied\n",
				2, 2, path, 2);
		else
			print_file(file, arg);
		ft_dell_file(&file);
		return (1);
	}
	return (0);
}

static void	dell_name(char **s1, char **s2, DIR **ptr)
{
	ft_strdel(s1);
	ft_strdel(s2);
	closedir(*ptr);
}

int			ft_is_file(t_arg *arg, char *name)
{
	char			*d_name;
	char			*f_name;
	DIR				*ptr;
	struct dirent	*dir;

	f_name = ft_strdup(name);
	if (!ft_strchr(name, '/') || !(d_name = ft_search_d_name(&f_name)))
		d_name = ft_strdup(".");
	if (!(ptr = opendir(d_name)))
		return (0);
	while ((dir = readdir(ptr)) != NULL)
	{
		if (!ft_strcmp(f_name, dir->d_name))
		{
			if (search_ifo_file(name, *dir, arg))
			{
				dell_name(&f_name, &d_name, &ptr);
				return (1);
			}
		}
	}
	dell_name(&d_name, &f_name, &ptr);
	ft_printf("{fd}ls: %{fd}s{fd}: No such file or directory\n", 2, 2, name, 2);
	return (1);
}
