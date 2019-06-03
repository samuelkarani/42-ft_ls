/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 23:18:25 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/30 20:06:33 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*create(char *name, time_t sec, long nsec)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	file->name = ft_strdup(name);
	file->sec = sec;
	file->nsec = nsec;
	file->next = NULL;
	return (file);
}

void	add_back(t_file **lst, char *name, time_t sec, long nsec)
{
	t_file *f;

	if (*lst)
	{
		f = *lst;
		while (f->next)
			f = f->next;
		f->next = create(name, sec, nsec);
	}
	else
		*lst = create(name, sec, nsec);
}

void	insert(t_file **lst, t_file *elem, t_file *prev, t_file *list)
{
	if (prev)
		prev->next = elem;
	else
		*lst = elem;
	elem->next = list;
}

void	add_back_s(t_file **lst, char *name, time_t sec, long nsec)
{
	t_file *elem;
	t_file *list;
	t_file *prev;

	elem = create(name, sec, nsec);
	list = *lst;
	prev = NULL;
	if (list)
		while (list)
		{
			if (l_cmp(list, elem) == 0)
			{
				insert(lst, elem, prev, list);
				break ;
			}
			else if (l_cmp(list, elem) && !list->next)
			{
				list->next = elem;
				break ;
			}
			prev = list;
			list = list->next;
		}
	else
		*lst = elem;
}

void	destroy(t_file **lst)
{
	t_file	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->name);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
}
