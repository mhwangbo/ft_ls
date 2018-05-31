/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:14:51 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/31 15:46:38 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	read_dir(t_dir *e)
{
	int				i;
	DIR				*dir;
	struct dirent	*tmp;
	char			*dir_tmp;
	char			*dir_join;
	if ((dir = opendir(e->dir_name)) == NULL)
	{
		ft_printf("ft_ls: %s: No such file or directoy\n", e->dir_name);
		exit (0);
	}
	e->max_dir = 0;
	i = -1;
	while ((tmp = readdir(dir)) != NULL)
		e->max_dir++;
	closedir(dir);
	free(tmp);
	e->dp = ft_memalloc(sizeof(struct dirent*) * e->max_dir);
	e->detail = ft_memalloc(sizeof(struct stat) * e->max_dir);
	i = 0;
	dir = opendir(e->dir_name);
	while (i < e->max_dir)
	{
		e->dp[i] = readdir(dir);
		dir_tmp = ft_strjoin(e->dir_name, "/");
		dir_join = ft_strjoin(dir_tmp, e->dp[i]->d_name);
		stat(dir_join, &e->detail[i]);
		i++;
		free(dir_tmp);
		free(dir_join);
	}
	closedir(dir);
}

/*
** 0 = no flags, 1 = -l, 2 = -R, 3 = -a, 4 = -r, 5 = -t
** -l : list in long format. before listing, a total sum of all file size displays
** -R : Recursively list subdirectories encountered.
** -a : Include directory entries whos names begin with a dot (.).
** -r : Reverse the order of the sort to get reverse lexicographical 
**      order or oldest entries first (or largest files last, if combined 
**      with sort by size)
** -t : Sort by time modified (most recently modified first)
*/

void	ls_flags_read(int ac, char **av, t_env *e, int i)
{
	if (ac == 1 || i == ac)
	{
		e->t[0].dir_name = ft_memalloc(sizeof(char) * 3);
		e->t[0].dir_name = "./\0";
		read_dir(&e->t[0]);
	}
	while (i < ac)
	{
		e->t[i - 1].dir_name = av[i];
		read_dir(&e->t[i - 1]);
		i++;
	}
}

void	ls_alpha_order(char **order, int no_print)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < no_print)
	{
		j = 0;
		while (j + 1 < no_print)
		{
			if (ft_strcmp(order[j], order[j + 1]) > 0)
			{
				tmp = order[j];
				order[j] = order[j + 1];
				order[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ls_print_zero(t_env *e, int no_dir)
{
	int		i;
	int		j;
	int		h;
	char	**order;
	int		no_print;
	size_t	space;
	
	j = -1;
	while (++j < no_dir)
	{
		i = -1;
		no_print = 0;
		space = 0;
		while (++i < e->t[j].max_dir)
			if (e->t[j].dp[i]->d_name[0] != '.')
			{
				space < ft_strlen(e->t[j].dp[i]->d_name) ? 
					space = ft_strlen(e->t[j].dp[i]->d_name) : 0;
				no_print++;
			}
		order = malloc(sizeof(char*) * no_print);
		h = 0;
		i = 0;
		while (h < no_print && i < e->t[j].max_dir)
		{
			if (e->t[j].dp[i]->d_name[0] != '.')
				order[h++] = e->t[j].dp[i]->d_name;
			i++;
		}
		ls_alpha_order(order, no_print);
		if (no_dir > 1)
			ft_printf("%s:\n", e->t[j].dir_name);
		for (int q = 0; q < no_print; q++)
			ft_printf("%-*s", (q == no_print - 1 ?
					ft_strlen(order[q]) : space + 1), order[q]);
		if (no_dir > 1 && j != no_dir - 1)
			ft_printf("\n");
		ft_printf("\n");
	}
}
void	ls_flags_send(t_env *e, int no_dir)
{
	if (e->flag[0] == 1)
		ls_print_zero(e, no_dir);
}

void	ls_flags(int ac, char **av)
{
	t_env	e;
	int		i;
	int		j;
	int		k;

	i = 0;
	ft_bzero(e.flag, sizeof(int) * 6);
	e.t = ft_memalloc(sizeof(t_dir) * (ac - 1));
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			j = -1;
			while (av[i][++j])
			{
				av[i][j] == 'l' ? e.flag[1] = 1 : 0;
				av[i][j] == 'R' ? e.flag[2] = 1 : 0;
				av[i][j] == 'a' ? e.flag[3] = 1 : 0;
				av[i][j] == 'r' ? e.flag[4] = 1 : 0;
				av[i][j] == 't' ? e.flag[5] = 1 : 0;
			}
		}
		else
			break ;
	}
	if (e.flag[1] == 0 && e.flag[2] == 0 && e.flag[3] == 0 &&
			e.flag[4] == 0 && e.flag[5] == 0)
		e.flag[0] = 1;
	ls_flags_read(ac, av, &e, i);
	ls_flags_send(&e, ac - i);
	k = -1;
	while (++k < (ac - 1))
	{
		free(e.t[k].detail);
		free(e.t[k].dp);
	}
	free(e.t);
}

int		main(int ac, char **av)
{
	if (ac < 1)
		return (0);
	ls_flags(ac, av);
	return (0);
}
