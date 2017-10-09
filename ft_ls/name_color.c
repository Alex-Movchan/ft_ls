/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 20:06:09 by amovchan          #+#    #+#             */
/*   Updated: 2017/10/01 20:06:12 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_get_color(char *acc)
{
	if (acc[0] == 'l')
		return (MAGENTA);
	else if (acc[0] == 's')
		return (GREEN);
	else if (acc[0] == 'p')
		return (BROWN);
	else if (acc[0] == 'b')
		return (BLEU_CYAN);
	else if (acc[0] == 'c')
		return (BLEU_BROWN);
	else if (acc[0] == 'd' && acc[8] == 'w' && (acc[9] == 't' || acc[9] == 'T'))
		return (BLACK_GREEN);
	else if (acc[0] == 'd' && acc[8] == 'w')
		return (BLACK_BROWN);
	else if (acc[0] == 'd')
		return (BLEU);
	else if (acc[3] == 's' || acc[3] == 'S')
		return (BLACK_RED);
	else if (acc[6] == 's' || acc[6] == 'l')
		return (BLACK_CYAN);
	else if (acc[3] == 'x' || acc[6] == 'x' || acc[9] == 'x')
		return (RED);
	return (NULL);
}

char		*name_color(char *name, char *acc)
{
	char	*src;
	char	*str;

	if (!(src = ft_get_color(acc)))
		return (name);
	src = ft_strjoin(src, name);
	str = ft_strjoin(src, EOC);
	ft_strdel(&src);
	ft_strdel(&name);
	return (str);
}

int			largest_name_len(t_file *file)
{
	int		max;
	int		len;
	t_file	*lst;

	max = 0;
	lst = file;
	while (lst)
	{
		if (max < (len = (int)ft_strlen(lst->name)))
			max = len;
		lst = lst->next;
	}
	max += 7;
	return (max);
}

void		last_file(t_file **file)
{
	while ((*file)->next)
		(*file) = (*file)->next;
}

char		*name_in_dr(char *name, char *file)
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
