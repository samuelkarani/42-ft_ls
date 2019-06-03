/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 00:58:23 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/30 20:06:42 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap(t_file *a, t_file *b)
{
	char		*tmp;
	time_t		tsec;
	long		tnsec;

	tmp = a->name;
	a->name = b->name;
	b->name = tmp;
	tsec = a->sec;
	a->sec = b->sec;
	b->sec = tsec;
	tnsec = a->nsec;
	a->nsec = b->nsec;
	b->nsec = tnsec;
}

void	sort(t_file *lst, int (*cmp)(t_file *, t_file *))
{
	t_file	*i;
	t_file	*j;
	int		flag;

	if (lst)
	{
		i = lst;
		while (i->next)
		{
			flag = 0;
			j = lst;
			while (j->next)
			{
				if ((*cmp)(j, j->next) == 0)
				{
					swap(j, j->next);
					flag = 1;
				}
				j = j->next;
			}
			if (flag == 0)
				break ;
			i = i->next;
		}
	}
}

void	filter(t_file *lst, t_file **result, int (*cmp)(char *))
{
	while (lst)
	{
		if ((*cmp)(lst->name))
			add_back(result, lst->name, lst->sec, lst->nsec);
		lst = lst->next;
	}
}

t_file	*filter_n(t_file *lst, int (*cmp)(char *))
{
	t_file	*ret;

	ret = NULL;
	filter(lst, &ret, cmp);
	return (ret);
}

void	reverse(t_file **lst)
{
	t_file *list;
	t_file *prev;
	t_file *next;

	list = *lst;
	prev = NULL;
	while (list)
	{
		next = list->next;
		list->next = prev;
		prev = list;
		list = next;
	}
	*lst = prev;
}
