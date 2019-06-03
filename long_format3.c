/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 00:49:59 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/29 19:57:18 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_owner(uid_t uid)
{
	char			*s;
	struct passwd	*u;

	u = getpwuid(uid);
	if (u)
		s = ft_strdup(u->pw_name);
	else
		asprintf(&s, "%ld", (long)uid);
	return (s);
}

char	*get_group(uid_t uid)
{
	char			*s;
	struct group	*g;

	g = getgrgid(uid);
	if (g)
		s = ft_strdup(g->gr_name);
	else
		asprintf(&s, "%ld", (long)uid);
	return (s);
}

void	get_time(struct timespec *t, char *buf[])
{
	time_t		now;
	char		*s;
	char		*p;
	time_t		mtime;
	int			gt;

	time(&now);
	mtime = (time_t)t->tv_sec;
	gt = mtime < now - LS_SIX_MONTHS || mtime > now + LS_SIX_MONTHS;
	s = ctime(&mtime);
	buf[5] = ft_strsub(s, 4, 3);
	buf[6] = ft_strsub(s, 8, 2);
	p = !gt ? ft_strsub(s, 11, 5) : ft_strsub(s, 20, 4);
	asprintf(&s, "%5s", p);
	buf[7] = s;
	free(p);
}

char	*device_no(dev_t st_rdev)
{
	char	*s;
	int		major;
	int		minor;
	char	*sma;
	char	*smi;

	major = major(st_rdev);
	minor = minor(st_rdev);
	major < 128 ? asprintf(&sma, "%d", major) : asprintf(&sma, "%#.8x", major);
	minor < 128 ? asprintf(&smi, "%d", minor) : asprintf(&smi, "%#.8x", minor);
	asprintf(&s, "%3s, %3s", sma, smi);
	free(sma);
	free(smi);
	return (s);
}

char	*get_link(char *fpath, char *name)
{
	char	*s;
	char	*r;
	char	*link;

	link = ft_strnew(LS_MAX_FILE_NAME);
	readlink(fpath, link, LS_MAX_FILE_NAME + 1);
	r = ft_strjoin(name, " -> ");
	s = ft_strjoin(r, link);
	free(link);
	free(r);
	return (s);
}
