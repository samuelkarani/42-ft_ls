/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:21:54 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/30 22:49:38 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*acl_extended(char *fpath)
{
	acl_t		a;
	ssize_t		xattr;
	char		*ret;

	ret = NULL;
	a = acl_get_file(fpath, ACL_TYPE_EXTENDED);
	xattr = listxattr(fpath, NULL, 0, XATTR_NOFOLLOW);
	if (xattr > 0)
		ret = ft_strdup("@");
	else if (a)
	{
		ret = ft_strdup("+");
		acl_free(a);
	}
	return (ret);
}

long long	get_values(char *buf[], char *name, char *prefix, int *special)
{
	struct stat	b;
	char		*s;
	char		*r;
	int			sp;
	int			link;

	sp = 0;
	s = prefix ? update_name(prefix, name) : ft_strdup(name);
	lstat(s, &b);
	link = (b.st_mode & S_IFMT) == S_IFLNK;
	buf[0] = join_and_free(mode(b.st_mode), acl_extended(s));
	asprintf(buf + 1, "%hd", b.st_nlink);
	buf[2] = g_flags[LS_G] ? ft_strdup("") : get_owner(b.st_uid);
	buf[3] = get_group(b.st_gid);
	if ((sp = check_special(b.st_mode)))
		r = device_no(b.st_rdev);
	else
		asprintf(&r, "%lld", b.st_size);
	if (special && !*special)
		*special = sp;
	buf[4] = r;
	get_time(g_flags[LS_U] ? &b.st_atimespec : &b.st_mtimespec, buf);
	buf[8] = link ? get_link(s, name) : ft_strdup(name);
	free(s);
	return ((long long)b.st_blocks);
}

long long	update_width(t_file *files, char *prefix, char *buf[])
{
	long long	total;
	int			i;
	int			l;
	int			special;

	total = 0;
	special = 0;
	while (files)
	{
		total += get_values(buf, files->name, prefix, &special);
		i = 0;
		while (i < LS_WIDTH_SIZE)
		{
			l = ft_strlen(buf[i]);
			if (l > g_width[i])
				g_width[i] = l;
			i++;
		}
		free_buf(buf);
		files = files->next;
	}
	if (special)
		g_width[4] = 8;
	return (total);
}

void		long_format(char *name, char *prefix, char **ret)
{
	char			*buf[LS_BUF_SIZE];

	get_values(buf, name, prefix, NULL);
	if (g_flags[LS_G])
		asprintf(ret, "%-*s %*s %-*s  %*s %*s %*s %s %s\n",
			11, buf[0],
			g_width[1], buf[1],
			g_width[3], buf[3],
			g_width[4], buf[4],
			g_width[5], buf[5],
			g_width[6], buf[6],
			buf[7],
			buf[8]);
	else
		asprintf(ret, "%-*s %*s %-*s  %-*s  %*s %*s %*s %s %s\n",
			11, buf[0],
			g_width[1], buf[1],
			g_width[2], buf[2],
			g_width[3], buf[3],
			g_width[4], buf[4],
			g_width[5], buf[5],
			g_width[6], buf[6],
			buf[7],
			buf[8]);
	free_buf(buf);
}
