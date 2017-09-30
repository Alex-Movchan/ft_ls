
#include "ft_ls.h"

static int	size_colum()
{
	struct winsize	size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return ((int)size.ws_col );
}

static int largest_name_len(t_file *file)
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

static int count_file(t_file *file)
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

static char	*ft_search_file(t_file *file, int n, int count, int max)
{
	t_file	*lst;

	lst = file;
	 n *= (max - count);
	while (lst && n)
	{
		lst = lst->next;
		n--;
	}
	if (lst)
		return (lst->name);
	else
		return (NULL);
}


void		print_colum(t_file *file, char *name, int i)
{
	int		len;
	int		size;
	int		count;
	int		n;
	int		colum;

	size = size_colum();
	len = largest_name_len(file);
	count = count_file(file);
	n = count % (size / len) > 0 ? 1 : 0;
	n += count / (size / len);
	i = n;
	while (file && i > 0)
	{
		colum = size / len;
		while (colum > 0)
		{
			if ((name = ft_search_file(file, n, colum, (size / len))) != NULL)
				ft_printf("%-*s", len, name);
			colum--;
		}
		if (i > 1)
			ft_printf("\n");
		file = file->next;
		i--;
	}
	ft_printf("\n");
}