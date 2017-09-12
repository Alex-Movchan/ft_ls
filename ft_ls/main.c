
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
	(*arg)->d = str[i] == 'd' ? 1 : (*arg)->d;
        (*arg)->u = str[i] == 'u' ? 1 : (*arg)->u;
        (*arg)->upper_r = str[i] == 'R' ? 1 : (*arg)->upper_r;
    }
}

static t_arg	*pars_arg(int len, char **av)
{
	int	i;
	t_arg	*arg;

	arg = (t_arg*)malloc(sizeof(t_arg));
	arg->upper_r = 0;
	arg->u = 0;
	arg->t = 0;
	arg->a = 0;
	arg->f = 0;
	arg->d = 0;
	arg->g = 0;
	arg->l = 0;
	arg->r = 0;
	i = 0;
	while (++i < len)
		pars_str(&arg, av[i]);
	return (arg);
}

int		main(int ac, char **av)
{
    t_arg   *arg;

    arg = NULL;
    if (ac != 1)
        arg = pars_arg(ac, av);

    return (0);
}

