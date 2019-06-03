/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:36:45 by smbaabu           #+#    #+#             */
/*   Updated: 2019/05/01 12:39:37 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		check_rfile_l(char *fpath)
{
	struct stat s;

	lstat(fpath, &s);
	return (S_ISREG(s.st_mode));
}

void	free_buf(char *buf[])
{
	int	i;

	i = 0;
	while (i < LS_BUF_SIZE)
		free(buf[i++]);
}

void	update_names(t_file *dfiles, char *prefix)
{
	char	*s;

	while (dfiles)
	{
		s = dfiles->name;
		dfiles->name = update_name(prefix, s);
		free(s);
		dfiles = dfiles->next;
	}
}
