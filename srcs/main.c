/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:36:57 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/06/08 22:09:12 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls(char *pos, int depth)
{
	DIR				*dp;
	struct dirent	*dir;
	struct stat		stat;
	char			**dir_name;
	int				number_dir;
	int				i;

	if ((dp = opendir(pos)) == NULL)
	{
		ft_printf("ls: %s: No such file or directory\n", pos);
		exit (0);
	}
	chdir(pos);
	number_dir = 0;
	while ((dir = readdir(dp)))
		number_dir++;
	closedir(dp);
	dir_name = ft_memalloc(sizeof(char*) * number_dir);
	chdir("..");
	dp = opendir(pos);
	chdir(pos);
	i = 0;
	ft_printf("%s: \n", pos);
	while ((dir = readdir(dp)))
	{
		ft_memset(&stat, 0, sizeof(struct stat));
		lstat(dir->d_name, &stat);
		if (S_ISDIR(stat.st_mode))
		{
			if (ft_strncmp(".", dir->d_name, 1) == 0 || ft_strncmp("..", dir->d_name, 2) == 0)
				continue ;
			dir_name[i] = dir->d_name;
			ft_ls(dir->d_name, depth + 4);
		}
		else
		{
			dir_name[i] = dir->d_name;
			ft_printf("%*s\n", depth, dir->d_name);
		}
	}
	chdir("..");
	closedir(dp);
	free(dir_name);
	ft_printf("\n");
}

int		main(int ac, char **av)
{
	t_env	e;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	e.position = ft_memalloc(sizeof(char*) * (ac - 1));
	while (++i < ac)
		e.position[j++] = av[i];
	i = 0;
	while (i < (ac - 1))
	{
		j = 0;
		while ((j + 1) < (ac - 1))
		{
			if (ft_strcmp(e.position[j], e.position[j + 1]) > 0)
			{
				tmp = e.position[j];
				e.position[j] = e.position[j + 1];
				e.position[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < (ac - 1))
	{
		ft_ls(e.position[i], 0);
		i++;
	}
	free(e.position);
	while (1);
	return (0);
}

