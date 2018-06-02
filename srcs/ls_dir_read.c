/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dir_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 18:35:21 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/06/01 22:30:38 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	ls_flags_read(int ac, char **av, t_env *e, int i)
{
	int		j;

	j = 0;
	ac == 1 ? i-- : 0;
	while (i < ac)
	{
		e->t[j].dir_name = ((i == ac || ac == 1) ? ft_strdup("./") : av[i]);
		read_dir(&e->t[j++]);
		i++;
	}
}
