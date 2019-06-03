/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 23:45:10 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/29 01:13:19 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		l_cmp(t_file *f1, t_file *f2)
{
	return (ft_strcmp(f1->name, f2->name) <= 0);
}

int		t_cmp(t_file *f1, t_file *f2)
{
	if (f1->sec == f2->sec)
		return (f1->nsec >= f2->nsec);
	return (f1->sec >= f2->sec);
}

int		check_not_dfile(char *fpath)
{
	return (!check_dfile(fpath));
}

int		check_dfile(char *fpath)
{
	struct stat s;

	if (g_flags[LS_L] || g_flags[LS_G])
		lstat(fpath, &s);
	else
		stat(fpath, &s);
	return (S_ISDIR(s.st_mode));
}

int		check_dfile_l(char *fpath)
{
	struct stat s;

	lstat(fpath, &s);
	return (S_ISDIR(s.st_mode));
}
