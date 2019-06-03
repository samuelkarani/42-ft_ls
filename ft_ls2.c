/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 00:32:26 by smbaabu           #+#    #+#             */
/*   Updated: 2019/05/01 12:38:11 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	order_files(t_file **files)
{
	if (!g_flags[LS_F])
	{
		if (g_flags[LS_T])
			sort(*files, &t_cmp);
		if (g_flags[LS_R])
			reverse(files);
	}
}

int		prepare(t_file *files, t_file **lines, char *prefix, int n)
{
	t_file		*f_files_p;
	char		*s;
	int			count;

	count = 0;
	f_files_p = files;
	while (files)
	{
		if (g_flags[LS_L] || g_flags[LS_G])
			long_format(files->name, prefix, &s);
		else
			asprintf(&s, "%s\n", files->name);
		add_back(lines, s, 0, 0);
		free(s);
		files = files->next;
		count++;
	}
	if (n > 1 && !g_flags[LS_D])
		destroy(&f_files_p);
	return (count);
}

void	print_lines(t_file *lines)
{
	t_file	*lines_p;

	lines_p = lines;
	while (lines)
	{
		ft_printf("%s", lines->name);
		lines = lines->next;
	}
	destroy(&lines_p);
}

int		print_files(t_file **files, char *prefix, int n)
{
	t_file		*f_files;
	t_file		*lines;
	long long	total;
	char		*buf[LS_BUF_SIZE];
	int			count;

	f_files = NULL;
	lines = NULL;
	order_files(files);
	if (n > 1 && !g_flags[LS_D])
		filter(*files, &f_files, &check_not_dfile);
	else
		f_files = *files;
	zero_initialize(g_width, LS_WIDTH_SIZE);
	if (g_flags[LS_L] || g_flags[LS_G])
		total = update_width(f_files, prefix, buf);
	count = prepare(f_files, &lines, prefix, n);
	if ((g_flags[LS_L] || g_flags[LS_G]) && n == 1
		&& check_dfile(prefix) && lines)
		ft_printf("total %lld\n", total);
	print_lines(lines);
	return (count);
}
