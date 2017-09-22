

#include "ft_ls.h"

static void    pars_str(t_arg **arg, char *str)
{
    int     i;

    i = -1;
    while (str[++i])
    {
        (*arg)->a = str[i] == 'a' ? 1 : (*arg)->a;
        (*arg)->f = str[i] == 'f' ? 1 : (*arg)->f;
        (*arg)->g = str[i] == 'g' ? 1 : (*arg)->g;
        (*arg)->l = str[i] == 'l' ? 1 : (*arg)->l;
        (*arg)->r = str[i] == 'r' ? 1 : (*arg)->r;
        (*arg)->t = str[i] == 't' ? 1 : (*arg)->t;
        (*arg)->u = str[i] == 'u' ? 1 : (*arg)->u;
		(*arg)->one = str[i] == '1' ? 1 : (*arg)->one;
        (*arg)->upper_r = str[i] == 'R' ? 1 : (*arg)->upper_r;
		(*arg)->upper_c = str[i] == 'C' ? 1 : (*arg)->upper_c;
    }
}

static t_arg   *pars_arg(int len, char **av)
{
    int     i;
    t_arg   *arg;

    arg = (t_arg*)malloc(sizeof(t_arg));
    arg->upper_r = 0;
	arg->upper_c = 0;
    arg->u = 0;
    arg->t = 0;
    arg->a = 0;
    arg->f = 0;
    arg->g = 0;
    arg->l = 0;
    arg->r = 0;
	arg->one = 0;
	arg->help = 0;
    i = 0;
    while (++i < len && av[i][0] == '-')
	{
		if (!ft_strcmp("--help", av[i]))
		{
			arg->help = 1;
			break ;
		}
		pars_str(&arg, av[i]);
	}
    return (arg);
}

int		ft_help()
{
	int	fd;
	char *line;

	if ((fd = open("../ft_ls/help.txt", O_RDONLY)) < 0)
	{
		ft_printf("Error opening sours help");
		return (-1);
	}
	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	return (0);
}

int           main(int ac, char **av)
{
	t_arg   *arg;
    char	*name;

	arg = pars_arg(ac, av);
	if (arg->help == 1)
	{
		free(arg);
		return (ft_help());
	}
	if (ac > 1 && av[ac -1][0] != '-')
		name = ft_strdup(av[ac - 1]);
	else
		name = ft_strdup(".");
	if (name[0] == '~')
		name = ft_strjoin(strndup(av[0], 10), av[ac - 1] + 1);
	ft_ls(arg, name);
	ft_strdel(&name);
	free(arg);
	return (0);
}

//iostl розмер термінала