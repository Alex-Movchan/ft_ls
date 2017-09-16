
#include "ft_ls.h"

static int		ft_strcmp_tplower(char *s1, char *s2)
{
	int		i;

	i = -1;
	while (s1[++i] && ft_tolower(s1[i]) == ft_tolower(s2[i]))
		;
	return (ft_tolower(s1[i])) - ft_tolower(s2[i]);
}

static int		first_arg(t_file **file)
{
	t_file	*lst;

	if ((*file)->next && ft_strcmp_tplower((*file)->name, (*file)->next->name) > 0)
	{
		lst = (*file)->next;
		(*file)->next = (*file)->next->next;
		lst->next = (*file);
		(*file) = lst;
		return (0);
	}
	return (1);
}

t_file	*sort_alpha(t_file *file)
{
	t_file	*lst;
	t_file	*tmp;
	t_file	*tmp2;

	lst = file;
	while (lst->next && lst->next->next)
	{
		if (ft_strcmp_tplower(lst->next->name, lst->next->next->name) > 0)
		{
			tmp = lst->next;
			tmp2 = lst->next->next->next;
			lst->next = lst->next->next;
			lst = lst->next;
			lst->next = tmp;
			tmp->next = tmp2;
			lst = file;
		}
		else
			lst = lst->next;
	}
	if (!first_arg(&file))
		sort_alpha(file);
	return (file);
}
