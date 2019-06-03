/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:21:41 by smbaabu           #+#    #+#             */
/*   Updated: 2019/05/01 12:34:58 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <libgen.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"

typedef struct		s_file
{
	char			*name;
	struct s_file	*next;
	time_t			sec;
	long			nsec;
}					t_file;

# define LS_BUF_SIZE 9
# define LS_WIDTH_SIZE 8
# define LS_MAX_FILE_NAME 512
# define LS_SIX_MONTHS 15552000

# define LS_NUM_FLAGS 11
# define LS_RR 0
# define LS_L 1
# define LS_R 2
# define LS_T 3
# define LS_A 4
# define LS_F 5
# define LS_G 6
# define LS_U 7
# define LS_D 8
# define LS_C 9
# define LS_Q 10

int	g_flags[LS_NUM_FLAGS];
int	g_width[LS_WIDTH_SIZE];

static const char g_flags_c[] = {
	'R',
	'l',
	'r',
	't',
	'a',
	'f',
	'g',
	'u',
	'd',
	'c',
	'q'
};

void				get_time_s(char *fpath, time_t *sec, long *nsec);
void				ft_ls(t_file **files, int valid_ops, int ops);
void				long_format(char *name, char *prefix, char **ret);
long long			update_width(t_file *files, char *prefix, char *buf[]);
int					print_files(t_file **files, char *prefix, int n);
void				order_files(t_file **files);
void				update_names(t_file *dfiles, char *prefix);
char				*mode(mode_t mode);
char				*get_owner(uid_t uid);
char				*get_group(uid_t uid);
void				get_time(struct timespec *t, char *buf[]);
char				*device_no(dev_t st_rdev);
char				*get_link(char *fpath, char *name);
void				free_buf(char *buf[]);

void				swap(t_file *a, t_file *b);
void				add_back_s(t_file **lst, char *name, time_t sec, long nsec);
void				add_back(t_file **lst, char *name, time_t sec, long nsec);
t_file				*create(char *name, time_t sec, long nsec);
void				sort(t_file *lst, int (*cmp)(t_file *, t_file *));
void				reverse(t_file **file_lst);
void				filter(t_file *lst, t_file **result, int (*cmp)(char *));
t_file				*filter_n(t_file *lst, int (*cmp)(char *));
void				destroy(t_file **lst);

char				*update_name(char *prefix, char *name);
void				initialize_flags(void);
int					l_cmp(t_file *f1, t_file *f2);
int					t_cmp(t_file *f1, t_file *f2);
int					check_rfile_l(char *fpath);
int					check_dfile(char *fpath);
int					check_special(mode_t mode);
int					check_dfile_l(char *fpath);
int					check_link(char *fpath);
int					check_hidden(char *fpath);
int					check_dot_dot(char *fpath);
int					check_dot_dot_n(char *fpath);
int					check_not_dfile(char *fpath);
int					fpath_ok(char *fpath);
void				zero_initialize(int arr[], int n);
void				clean_exit(char illegal);
void				ft_ls_error(char *fpath);

#endif
