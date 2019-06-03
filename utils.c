/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:08:57 by smbaabu           #+#    #+#             */
/*   Updated: 2019/05/01 12:31:09 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*update_name(char *prefix, char *name)
{
	char	*r;
	char	*s;

	r = ft_strjoin("/", name);
	s = ft_strjoin(prefix, r);
	free(r);
	return (s);
}

int		fpath_ok(char *fpath)
{
	struct stat b;

	return (lstat(fpath, &b) == 0);
}

void	zero_initialize(int arr[], int n)
{
	int i;

	i = 0;
	while (i < n)
		arr[i++] = 0;
}

void	ft_ls_error(char *fpath)
{
	fprintf(stderr, "ls: %s: %s\n", fpath, strerror(errno));
}

void	clean_exit(char illegal)
{
	fprintf(stderr, "ls: illegal option -- %c\n", illegal);
	fprintf(stderr, "usage: ls [-Rlrtafgudcq] "
		"[file ...]\n");
	exit(1);
}
