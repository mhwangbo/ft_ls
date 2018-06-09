/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:11:15 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/06/08 22:09:08 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


/*
** [0] : no flag
** -l : List in long format.  (See
**           below.)  If the output is to a terminal, a total sum for all the
**           file sizes is output on a line before the long listing.
** -R : Recursively list subdirectories encountered.
** -a : Include directory entries whose names begin with a dot (.)
** -r : Reverse the order of the sort to get reverse lexicographical order
**           or the oldest entries first (or largest files last, if combined
**           with sort by size
** -t : Sort by time modified (most recently modified first) before sort-
**           ing the operands by lexicographical order.
*/

void	ft_ls_save_dir(char *pos, t_dir *d, int depth)
{
	int		i;

	i = 0;
	while((d->dir = readdir(d->dp)))
	{
		ft_memset(&d->stat, 0, sizeof(struct stat));
		lstat(d->dir->d_name, &d->stat);
		if (S_ISDIR(d->stat.st_mode))
		{
			if (ft_strncmp(".", d->dir->d_name, 1) == 0 ||
					ft_strncmp("..", d->dir->d_name, 2) == 0)
				continue;
			dir->dir_name[i] = dir->d_name;
			ft_ls(dir->d_name[i], depth + 1);
		}
		else
			d->dir_name[i] = d->dir->d_name;
	}
}

void	ft_ls(char *pos, int depth)
{
	t_dir	d;

	d.depth = depth;
	if ((d.dp = opendir(pos)) == NULL)
	{
		ft_printf("ls: %s: No such file or directory\n", pos);
		exit (0);
	}
	chdir(pos);
	number_dir = 0;
	while ((d.dir = readdir(d.dp)))
		number_dir++;
	closedir(d.dp);
	d.dir_name = ft_memalloc(sizeof(char*) * number_dir);
	chdir("..");
	d.dp = opendir(pos);
	chdir(pos);
	ft_ls_save_dir(pos, &d.dir, depth);
	chdir("..");
	closedir(d.dp);
	free(d.dir_name);
}

void	ft_ls_flag(int ac, char **av, t_env *e, int *i)
{
	while (i < ac && ft_strncmp("-", av[i], 1))
	{
		ft_strchr(av[i], 'l') != NULL ? e->flag[1] = 1 : 0;
		ft_strchr(av[i], 'R') != NULL ? e->flag[2] = 1 : 0;
		ft_strchr(av[i], 'a') != NULL ? e->flag[3] = 1 : 0;
		ft_strchr(av[i], 'r') != NULL ? e->flag[4] = 1 : 0;
		ft_strchr(av[i], 't') != NULL ? e->flag[5] = 1 : 0;
		i++;
	}
	if (e->flag[1] == 0 && e->flag[2] == 0 && e->flag[3] == 0 &&
			e->flag[4] == 0 && e->flag[5] == 0)
		e->flag[0] = 1;
}

void	ft_ls_change_alpha(int max, char **str)
{
	int		i;
	int		j;

	i = 0;
	while (i < max)
	{
		j = 0;
		while((j + 1) < max)
		{
			if (ft_strcmp(str[j], str[j + 1]) > 0)
			{
				tmp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int		main(int ac, char **av)
{
	t_env	e;
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	j = 0;
	e.position = ft_memalloc(sizeof(char*) * (ac - 1));
	ft_bzero(e.flag, sizeof(int) * 6);
	ft_ls_flag(ac, av, &e, &i);
	while (i < ac)
		e.position[j++] = av[i++];
	ft_ls_change_alpha(ac - 1, e.position);
	i = 0;
	while (i < (ac - 1))
	{
		ft_ls((ac == 1 ? "./" : e.position[i]), 0);
		i++;
	}
	free(e.position);
	while (1);
	return (0);
}
