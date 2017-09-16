
#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

typedef struct		s_arg
{
	int				l;
	int				upper_r;
	int				a;
    int				r;
    int				t;
    int				u;
    int				f;
    int				g;
	int				one;
}					t_arg;

typedef struct		s_file
{
	char			*access;
	nlink_t			st_nlink;
	char 			*pw_name;
	char			*gr_name;
	off_t			st_size;
	time_t			st_time;
	char			*name;
	blkcnt_t		blok;
	struct s_file	*next;
	struct s_file	*previous;
}					t_file;

t_file				*read_dir(DIR *ptr, t_arg *arg, char *name);
void				ft_ls(t_arg *arg, char *name);
t_file				*sort_tim(t_file *file);
t_file				*sort_alpha(t_file *file);
void				previous_communication(t_file **file);
void				last_file(t_file **file);
#endif
