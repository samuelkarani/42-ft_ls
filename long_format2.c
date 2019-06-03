/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 00:45:13 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/29 00:56:24 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	type(mode_t mode)
{
	char c;

	c = '?';
	if ((mode & S_IFMT) == S_IFBLK)
		c = 'b';
	if ((mode & S_IFMT) == S_IFCHR)
		c = 'c';
	if ((mode & S_IFMT) == S_IFDIR)
		c = 'd';
	if ((mode & S_IFMT) == S_IFLNK)
		c = 'l';
	if ((mode & S_IFMT) == S_IFSOCK)
		c = 's';
	if ((mode & S_IFMT) == S_IFIFO)
		c = 'p';
	if ((mode & S_IFMT) == S_IFREG)
		c = '-';
	return (c);
}

char	user(mode_t mode)
{
	char c;

	if (!(mode & S_IXUSR) && (mode & S_ISUID))
		c = 'S';
	else if ((mode & S_IXUSR) && (mode & S_ISUID))
		c = 's';
	else if (mode & S_IXUSR)
		c = 'x';
	else
		c = '-';
	return (c);
}

char	group(mode_t mode)
{
	char c;

	if (!(mode & S_IXGRP) && (mode & S_ISGID))
		c = 'S';
	else if ((mode & S_IXGRP) && (mode & S_ISGID))
		c = 's';
	else if (mode & S_IXGRP)
		c = 'x';
	else
		c = '-';
	return (c);
}

char	other(mode_t mode)
{
	char c;

	if (!(mode & S_IXOTH) && (mode & S_ISVTX))
		c = 'T';
	else if ((mode & S_IXOTH) && (mode & S_ISVTX))
		c = 't';
	else if (mode & S_IXOTH)
		c = 'x';
	else
		c = '-';
	return (c);
}

char	*mode(mode_t mode)
{
	char	*s;

	s = ft_strnew(10);
	s[0] = type(mode);
	s[1] = (mode & S_IRUSR) ? 'r' : '-';
	s[2] = (mode & S_IWUSR) ? 'w' : '-';
	s[3] = user(mode);
	s[4] = (mode & S_IRGRP) ? 'r' : '-';
	s[5] = (mode & S_IWGRP) ? 'w' : '-';
	s[6] = group(mode);
	s[7] = (mode & S_IROTH) ? 'r' : '-';
	s[8] = (mode & S_IWOTH) ? 'w' : '-';
	s[9] = other(mode);
	return (s);
}
