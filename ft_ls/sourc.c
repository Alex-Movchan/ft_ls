/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sourc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 20:00:35 by amovchan          #+#    #+#             */
/*   Updated: 2017/10/01 20:00:37 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			size_colum(void)
{
	struct winsize	size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return ((int)size.ws_col);
}

int			count_file(t_file *file)
{
	int		i;
	t_file	*lst;

	lst = file;
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static int	*init_max(int *max)
{
	max = (int*)malloc(sizeof(int) * 6);
	max[0] = 0;
	max[1] = 0;
	max[2] = 0;
	max[3] = 0;
	max[4] = 0;
	max[5] = 0;
	return (max);
}

int			*largestelem(t_file *file, t_arg *arg)
{
	int		*max;
	t_file	*lst;

	lst = file;
	max = init_max(NULL);
	while (lst)
	{
		if (max[0] < ft_len_int((int)lst->st_nlink))
			max[0] = ft_len_int((int)lst->st_nlink);
		if (max[1] < ft_len_int((int)lst->st_size))
			max[1] = ft_len_int((int)lst->st_size);
		if (arg->l && max[2] < (int)ft_strlen(lst->pw_name))
			max[2] = (int)ft_strlen(lst->pw_name);
		if (max[3] < (int)ft_strlen(lst->gr_name))
			max[3] = (int)ft_strlen(lst->gr_name);
		if (max[4] < ft_len_int((int)lst->st_gid))
			max[4] = ft_len_int((int)lst->st_gid);
		if (max[5] < ft_len_int((int)lst->st_uid))
			max[5] = ft_len_int((int)lst->st_uid);
		lst = lst->next;
	}
	max[0]++;
	max[1]++;
	return (max);
}

int			ft_total(t_file *file, t_arg *arg)
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
	return (res);
}
