/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 18:30:08 by amovchan          #+#    #+#             */
/*   Updated: 2017/10/09 19:48:01 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_dell_file(t_file **file)
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
		ft_strdel(&(leaks->gr_name));
		ft_strdel(&(leaks->pw_name));
		ft_strdel(&(leaks->path));
		ft_strdel(&(leaks->d_name));
		free(leaks);
	}
}

static void	ft_recursoin(t_file *file, t_arg *arg, char *name)
{
	t_file	*lst;
	char	*src;
	char	*buf;

	lst = file;
	while (lst)
	{
		if (lst->access[0] == 'd' && ft_strcmp(".", lst->d_name) &&
				ft_strcmp("..", lst->d_name) &&
				!(arg->a == 0 && lst->d_name[0] == '.'))
		{
			if (name[ft_strlen(name) - 1] != '/')
			{
				buf = ft_strjoin(name, "/");
				src = ft_strjoin(buf, lst->d_name);
				ft_strdel(&buf);
			}
			else
				src = ft_strjoin(name, lst->d_name);
			ft_ls(arg, src);
			ft_strdel(&src);
		}
		lst = lst->next;
	}
}

static void	ft_get_link_and_cilor(t_file **file, t_arg *arg)
{
	t_file	*lst;

	lst = *file;
	while (lst)
	{
		lst->name = file_name_and_links(lst->path, lst->access, lst->name, arg);
		lst = lst->next;
	}
}

void		ft_ls(t_arg *arg, char *name)
{
	DIR		*ptr;
	t_file	*file;

	file = NULL;
	if (!(ptr = opendir(name)))
	{
		if (!ft_is_file(arg, name))
			ft_printf("%{fd}s\n", 2, "Error opening");
		return ;
	}
	read_dir(ptr, arg, name, &file);
	closedir(ptr);
	if (!file)
		return ;
	if (arg->upper_g || arg->g || arg->l || arg->n)
		ft_get_link_and_cilor(&file, arg);
	if (arg->upper_r)
		ft_printf("%s:\n", name);
	print_file(file, arg);
	if (arg->upper_r)
		ft_recursoin(file, arg, name);
	ft_dell_file(&file);
}
