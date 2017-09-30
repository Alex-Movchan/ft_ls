
#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <sys/xattr.h>
# include <sys/acl.h>

typedef struct		s_arg
{
	int				l;
	int				upper_r;
	int				upper_c;
	int				a;
    int				r;
    int				t;
    int				u;
    int				f;
    int				g;
	int				one;
	int				help;
}					t_arg;

typedef struct		s_file
{
	char			*access;
	nlink_t			st_nlink;
	char 			*pw_name;
	char			*gr_name;
	off_t			st_size;
	time_t			st_time;
	time_t			st_nano;
	char			*name;
	blkcnt_t		blok;
	char			*atribut;
	struct s_file	*next;
	struct s_file	*previous;
}					t_file;

void				read_dir(DIR *ptr, t_arg *arg, char *name, t_file **begin);
void				ft_ls(t_arg *arg, char *name);
void				last_file(t_file **file);
int					ft_total(t_file *file, t_arg *arg);
void				print_revers(t_file *file, t_arg *arg);
void				print_file(t_file *file, t_arg *arg);
int					*largestelem(t_file *file);
void				print_colum(t_file *file, char *name, int i);
char  			 	*ft_access(struct stat buf, char *d_name);
void				add_alpha_file(t_file **begin, t_file *file);
void				add_time_file(t_file **begin, t_file *file);
char				*file_name_and_links(char *path, char link, char *name, t_arg *arg);



#endif
