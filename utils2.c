/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 23:44:58 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/29 01:13:19 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		check_link(char *fpath)
{
	struct stat s;

	if (g_flags[LS_L] || g_flags[LS_G])
		lstat(fpath, &s);
	else
		stat(fpath, &s);
	return (S_ISLNK(s.st_mode));
}

int		check_hidden(char *fpath)
{
	return (fpath[0] == '.');
}

int		check_dot_dot(char *fpath)
{
	return (ft_strcmp(fpath, ".") == 0 || ft_strcmp(fpath, "..") == 0);
}

int		check_dot_dot_n(char *fpath)
{
	return (!check_dot_dot(fpath));
}

int		check_special(mode_t mode)
{
	return (((mode & S_IFMT) == S_IFBLK) || ((mode & S_IFMT) == S_IFCHR));
}
