/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 22:40:16 by smbaabu           #+#    #+#             */
/*   Updated: 2019/05/01 12:37:10 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_time_s(char *fpath, time_t *sec, long *nsec)
{
	struct stat b;

	if (g_flags[LS_L] || g_flags[LS_G] || g_flags[LS_T])
		lstat(fpath, &b);
	else
		stat(fpath, &b);
	*sec = g_flags[LS_U] ? b.st_atimespec.tv_sec : b.st_mtimespec.tv_sec;
	*nsec = g_flags[LS_U] ? b.st_atimespec.tv_nsec : b.st_mtimespec.tv_nsec;
	*sec = g_flags[LS_C] ? b.st_ctimespec.tv_sec : *sec;
	*nsec = g_flags[LS_C] ? b.st_ctimespec.tv_nsec : *nsec;
}

void	parse_flags(char *s)
{
	int		idx;

	while (*s)
	{
		if ((idx = ft_stridx(g_flags_c, *s)) == -1)
			clean_exit(*s);
		g_flags[idx] = 1;
		s++;
	}
}

void	handle_operands(t_file **files, char *s, int *ops)
{
	int		end_flgs;
	time_t	sec;
	long	nsec;

	end_flgs = 0;
	if (s[0] == '-' && s[1] && !end_flgs)
		parse_flags(s + 1);
	else
	{
		end_flgs = 1;
		if (fpath_ok(s))
		{
			sec = 0;
			nsec = 0;
			if (g_flags[LS_T] && !g_flags[LS_F])
				get_time_s(s, &sec, &nsec);
			add_back_s(files, s, sec, nsec);
			ops[1]++;
		}
		else
			ft_ls_error(s);
		ops[0]++;
	}
}

int		main(int ac, char **av)
{
	t_file	*files;
	int		i;
	int		ops[2];

	zero_initialize(g_flags, LS_NUM_FLAGS);
	zero_initialize(ops, 2);
	files = NULL;
	if (ac > 1)
	{
		i = 1;
		while (i < ac)
			handle_operands(&files, av[i++], ops);
		if (ops[0] && !ops[1])
			exit(0);
	}
	if (!files)
		add_back(&files, ".", 0, 0);
	ft_ls(&files, !ops[1] ? 1 : ops[1], ops[0]);
	return (0);
}
