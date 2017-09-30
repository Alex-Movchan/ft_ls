#include "ft_ls.h"

static char	ft_get_atribut(char *path)
{
	acl_t		acl;
	char		c;
	acl_entry_t	entry_p;
	char		*buf;

	c = ' ';
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry_p) == -1)
		acl_free(&acl);
	if (acl)
		c = '+';
	if (listxattr(path, buf, 1, XATTR_NOFOLLOW) > 0)
		c = '@';
	return (c);
}

char  	 	*ft_access(struct stat buf, char *d_name)
{
	char    *mod;
	int     i;

	i = 0;
	mod = (char*)malloc(sizeof(char) * 12);
	mod[i] = S_ISFIFO(buf.st_mode) ? 'p' : mod[i];
	mod[i] = S_ISCHR(buf.st_mode) ? 'c' : mod[i];
	mod[i] = S_ISDIR(buf.st_mode) ? 'd' :mod[i];
	mod[i] = S_ISBLK(buf.st_mode) ? 'b' : mod[i];
	mod[i] = S_ISREG(buf.st_mode) ? '-' : mod[i];
	mod[i] = S_ISLNK(buf.st_mode) ? 'l' : mod[i];
	mod[i] = S_ISSOCK(buf.st_mode) ? 's' : mod[i];
	mod[++i] = (buf.st_mode & S_IRUSR) ? 'r' : '-';
	mod[++i] = (buf.st_mode & S_IWUSR) ? 'w' : '-';
	mod[++i] = (buf.st_mode & S_IXUSR) ? 'x' : '-';
	mod[++i] = (buf.st_mode & S_IRGRP) ? 'r' : '-';
	mod[++i] = (buf.st_mode & S_IWGRP) ? 'w' : '-';
	mod[++i] = (buf.st_mode & S_IXGRP) ? 'x' : '-';
	mod[++i] = (buf.st_mode & S_IROTH) ? 'r' : '-';
	mod[++i] = (buf.st_mode & S_IWOTH) ? 'w' : '-';
	mod[++i] = (buf.st_mode & S_IXOTH) ? 'x' : '-';
	mod[++i] = ft_get_atribut(d_name);
	mod[++i] = '\0';
	return (mod);
}

char		*file_name_and_links(char *path, char link, char *name, t_arg *arg)
{
	char	*src;
	char	buf[PATH_MAX];
	char	*str;

	if (link == 'l' && (arg->l == 1 || arg->g == 1))
	{
		readlink(path, buf, sizeof(buf));
		src = ft_strjoin(name, " -> ");
		str = ft_strjoin(src, buf);
		ft_strdel(&src);
		return (str);
	}
	return (ft_strdup(name));
}