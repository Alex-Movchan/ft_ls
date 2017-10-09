/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 18:29:22 by amovchan          #+#    #+#             */
/*   Updated: 2017/10/01 18:29:33 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	ft_get_atribut(char *path)
{
	acl_t		acl;
	char		c;
	acl_entry_t	entry_p;
	char		*buf;

	c = ' ';
	buf = NULL;
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry_p) == -1)
		acl_free(&acl);
	if (acl)
		c = '+';
	if (listxattr(path, buf, 1, XATTR_NOFOLLOW) > 0)
		c = '@';
	return (c);
}

char		*ft_access(struct stat buf, char *d_name, char *mod)
{
	mod[0] = S_ISFIFO(buf.st_mode) ? 'p' : mod[0];
	mod[0] = S_ISCHR(buf.st_mode) ? 'c' : mod[0];
	mod[0] = S_ISDIR(buf.st_mode) ? 'd' : mod[0];
	mod[0] = S_ISBLK(buf.st_mode) ? 'b' : mod[0];
	mod[0] = S_ISREG(buf.st_mode) ? '-' : mod[0];
	mod[0] = S_ISLNK(buf.st_mode) ? 'l' : mod[0];
	mod[0] = S_ISSOCK(buf.st_mode) ? 's' : mod[0];
	mod[1] = (buf.st_mode & S_IRUSR) ? 'r' : '-';
	mod[2] = (buf.st_mode & S_IWUSR) ? 'w' : '-';
	mod[3] = (buf.st_mode & S_IXUSR) ? 'x' : '-';
	mod[4] = (buf.st_mode & S_IRGRP) ? 'r' : '-';
	mod[5] = (buf.st_mode & S_IWGRP) ? 'w' : '-';
	mod[6] = (buf.st_mode & S_IXGRP) ? 'x' : '-';
	mod[7] = (buf.st_mode & S_IROTH) ? 'r' : '-';
	mod[8] = (buf.st_mode & S_IWOTH) ? 'w' : '-';
	mod[9] = (buf.st_mode & S_IXOTH) ? 'x' : '-';
	mod[10] = ft_get_atribut(d_name);
	if (buf.st_mode & S_ISUID)
		mod[3] = (buf.st_mode & S_IXUSR) ? 's' : 'S';
	if (buf.st_mode & S_ISGID)
		mod[6] = (buf.st_mode & S_IXGRP) ? 's' : 'l';
	if (buf.st_mode & S_ISVTX)
		mod[9] = (buf.st_mode & S_IXOTH) ? 't' : 'T';
	return (mod);
}

char		*file_name_and_links(char *path, char *acc, char *name, t_arg *arg)
{
	char	*src;
	char	buf[PATH_MAX];
	char	*str;

	if (acc[0] == 'l' && (arg->l == 1 || arg->g == 1))
	{
		readlink(path, buf, sizeof(buf));
		src = ft_strjoin(name, " -> ");
		str = ft_strjoin(src, buf);
		ft_strdel(&src);
		return (str);
	}
	return (name);
}
