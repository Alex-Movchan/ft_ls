/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 20:08:53 by amovchan          #+#    #+#             */
/*   Updated: 2017/10/01 20:08:59 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define BLEU "\e[34m"
# define MAGENTA "\e[35m"
# define GREEN "\e[32m"
# define RED "\e[31m"
# define BROWN "\e[33m"
# define BLEU_CYAN "\e[34;46m"
# define BLEU_BROWN "\e[34;43m"
# define BLACK_RED "\e[30;41m"
# define BLACK_CYAN "\e[30;46m"
# define BLACK_GREEN "\e[30;42m"
# define BLACK_BROWN "\e[30;43m"
# define EOC "\e[0;0m"

typedef struct		s_arg {
	int				l;
	int				upper_r;
	int				upper_g;
	int				a;
	int				r;
	int				t;
	int				u;
	int				f;
	int				g;
	int				one;
	int				n;
	int				d;
}					t_arg;

typedef struct		s_file
{
	char			*access;
	char			*path;
	char			*color;
	nlink_t			st_nlink;
	char			*pw_name;
	char			*gr_name;
	uid_t			st_uid;
	gid_t			st_gid;
	off_t			st_size;
	time_t			st_time;
	time_t			st_nano;
	char			*name;
	char			*d_name;
	blkcnt_t		blok;
	struct s_file	*next;
	struct s_file	*previous;
}					t_file;

void				read_dir(DIR *ptr, t_arg *arg, char *name, t_file **begin);
void				ft_ls(t_arg *arg, char *name);
void				last_file(t_file **file);
int					ft_total(t_file *file, t_arg *arg);
void				print_file(t_file *file, t_arg *arg);
int					*largestelem(t_file *file, t_arg *arg);
void				print_colum(t_file *file, int i);
char				*ft_access(struct stat buf, char *d_name, char *mod);
void				add_alpha_file(t_file **begin, t_file *file);
void				add_time_file(t_file **begin, t_file *file);
char				*file_name_and_links(char *path, char *acc,
								char *name, t_arg *arg);
char				*name_color(char *name, char *acc);
int					size_colum();
void				ft_dell_file(t_file **file);
int					count_file(t_file *file);
int					largest_name_len(t_file *file);
void				print_colum_rev(t_file *file, int i);
t_file				*file_data(struct stat buf, t_arg *arg);
int					ft_is_file(t_arg *arg, char *name);
char				*ft_get_color(char *acc);
char				*name_in_dr(char *name, char *file);
void				sort_nano(t_file *lst, t_file *file);

#endif
