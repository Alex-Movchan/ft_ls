/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 19:32:44 by amovchan          #+#    #+#             */
/*   Updated: 2017/10/03 16:44:48 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		pars_str(t_arg **arg, char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		(*arg)->a = str[i] == 'a' ? 1 : (*arg)->a;
		(*arg)->d = str[i] == 'd' ? 1 : (*arg)->d;
		(*arg)->g = str[i] == 'g' ? 1 : (*arg)->g;
		(*arg)->l = str[i] == 'l' ? 1 : (*arg)->l;
		(*arg)->r = str[i] == 'r' ? 1 : (*arg)->r;
		(*arg)->t = str[i] == 't' ? 1 : (*arg)->t;
		(*arg)->u = str[i] == 'u' ? 1 : (*arg)->u;
		(*arg)->n = str[i] == 'n' ? 1 : (*arg)->n;
		(*arg)->one = str[i] == '1' ? 1 : (*arg)->one;
		(*arg)->upper_r = str[i] == 'R' ? 1 : (*arg)->upper_r;
		(*arg)->upper_g = str[i] == 'G' ? 1 : (*arg)->upper_g;
		if (str[i] == 'f')
		{
			(*arg)->a = 1;
			(*arg)->f = 1;
		}
	}
}

static t_arg	*init_arg(t_arg *arg)
{
	arg = (t_arg *)malloc(sizeof(t_arg));
	arg->upper_r = 0;
	arg->upper_g = 0;
	arg->u = 0;
	arg->t = 0;
	arg->a = 0;
	arg->f = 0;
	arg->g = 0;
	arg->d = 0;
	arg->l = 0;
	arg->n = 0;
	arg->r = 0;
	arg->one = 0;
	return (arg);
}

static t_arg	*pars_arg(int len, char **av)
{
	int		i;
	int		j;
	t_arg	*arg;

	i = 0;
	arg = init_arg(NULL);
	while (++i < len && av[i][0] == '-')
	{
		j = 0;
		while (av[i][++j])
			if (!ft_strchr("RGutafgdlnr1", av[i][j]))
			{
				free(arg);
				ft_printf("%susage: ls [-RGutafgdlnr1] [file ...]%s\n",
					RED, EOC);
				return (NULL);
			}
		pars_str(&arg, av[i]);
	}
	return (arg);
}

static void		ls_myni_fil(int ac, char **av, t_arg *arg)
{
	int		i;
	char	*name;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
			continue ;
		name = ft_strdup(av[i]);
		if (i + 1 != ac && (av[ac - 1][0] != '-'))
			ft_printf("%s: \n", name);
		ft_ls(arg, name);
		ft_strdel(&name);
	}
}

int				main(int ac, char **av)
{
	t_arg	*arg;
	char	*name;

	if (!(arg = pars_arg(ac, av)))
		return (0);
	if ((ac > 1 && av[ac - 1][0] == '-') || ac == 1)
		name = ft_strdup(".");
	else
	{
		ls_myni_fil(ac, av, arg);
		free(arg);
		return (0);
	}
	ft_ls(arg, name);
	ft_strdel(&name);
	free(arg);
	return (0);
}
