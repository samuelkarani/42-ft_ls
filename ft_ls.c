/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:15:14 by smbaabu           #+#    #+#             */
/*   Updated: 2019/05/01 12:35:58 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	handle_time(t_file **files, char *name, char *s)
{
	time_t			sec;
	long			nsec;

	sec = 0;
	nsec = 0;
	if (g_flags[LS_T])
		get_time_s(s, &sec, &nsec);
	add_back_s(files, name, sec, nsec);
}

void	get_files(char *dpath, t_file **files)
{
	DIR				*dir;
	struct dirent	*dir_entry;
	char			*s;

	if ((dir = opendir(dpath)))
	{
		while ((dir_entry = readdir(dir)))
		{
			s = update_name(dpath, dir_entry->d_name);
			if (!fpath_ok(s) || (check_hidden(dir_entry->d_name)
				&& !g_flags[LS_A] && !g_flags[LS_F])
				|| (g_flags[LS_Q] && !check_rfile_l(dir_entry->d_name)))
			{
				free(s);
				continue ;
			}
			handle_time(files, dir_entry->d_name, s);
			free(s);
		}
		closedir(dir);
	}
	else
		ft_ls_error(basename(dpath));
}

void	get_dfiles(t_file *files, t_file **dfiles, char *prefix, int n)
{
	t_file	*lst;

	if (n == 1)
		lst = filter_n(files, &check_dot_dot_n);
	else
		lst = files;
	if (prefix)
		update_names(lst, prefix);
	if (g_flags[LS_RR])
		filter(lst, dfiles, &check_dfile_l);
	else
		filter(lst, dfiles, &check_dfile);
	if (*dfiles)
		order_files(dfiles);
	if (n == 1)
		destroy(&lst);
}

void	handle_dfiles(t_file *dfiles, t_file **files, int count)
{
	t_file	*dfiles_p;

	if (count)
		ft_printf("\n");
	destroy(files);
	dfiles_p = dfiles;
	while (dfiles)
	{
		ft_printf("%s:\n", dfiles->name);
		add_back_s(files, dfiles->name, dfiles->sec, dfiles->nsec);
		ft_ls(files, 1, 0);
		destroy(files);
		dfiles = dfiles->next;
		if (dfiles)
			ft_printf("\n");
	}
	destroy(&dfiles_p);
}

void	ft_ls(t_file **files, int valid_ops, int ops)
{
	t_file	*dfiles;
	char	*s;
	int		count;

	count = 0;
	s = NULL;
	if (valid_ops == 1 && check_dfile((*files)->name) && !g_flags[LS_D])
	{
		s = ft_strdup((*files)->name);
		destroy(files);
		get_files(s, files);
	}
	if (ops > valid_ops && valid_ops == 1 && s)
		ft_printf("%s:\n", s);
	count = print_files(files, s, valid_ops);
	dfiles = NULL;
	if ((valid_ops > 1 || g_flags[LS_RR]) && !g_flags[LS_D])
		get_dfiles(*files, &dfiles, s, valid_ops);
	free(s);
	if (dfiles)
		handle_dfiles(dfiles, files, count);
	else
		destroy(files);
}
