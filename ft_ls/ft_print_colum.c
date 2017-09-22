
#include "ft_ls.h"

static int	size_colum()
{
	struct winsize	size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return ((int)size.ws_col);
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
	max += 2;
	return (max);
}

static int count_file(t_file *file, t_arg *arg)
{
	int		i;
	t_file	*lst;

	lst = file;
	i = 0;
	while (lst)
	{
		if (arg->a == 0 && lst->name[0] == '.')
			;
		else
			i++;
		lst = lst->next;
	}
	return (i);
}

void		print_colum(t_file *file, t_arg *arg)
{
	int		len;
	int		size;
	int		line;

	size = size_colum();
	len = largest_name_len(file);
	//size -= 10;
	line = size / len;
	while (file)
	{
		if (arg->a == 0 && file->name[0] == '.')
		{
			file = file->next;
			continue ;
		}
		if (file->access[0] == 'd')
			ft_printf("%{green}-*s{eoc}", len, file->name);
		else if (file->access[0] == 'l')
			ft_printf("%{bleu}-*s{eoc}", len, file->name);
		else
			ft_printf("%-*s", len, file->name);
		line--;
		if (!line)
		{
			ft_printf("\n");
			line = size / len;
		}
		file = file->next;
	}
	ft_printf("\n");
}