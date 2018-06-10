/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:09:43 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/06/09 17:40:41 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls_dir_print_property(t_info *info)
{
	if (info->file_stat.st_mode & S_IFMT == S_IFREG)
	{
		info->dir->property[0] = '-';
		break ;
	}
	else if (info->file_stat.st_mode & S_IFMT == S_IFDIR)
	{
		info->dir->property[0] = 'd';
		ft_strcpy(info->col_start, "^[[0;34m");
		break ;
	}
	else if (info->file_stat.st_mode & S_IFMT == S_IFIFO)
	{
		info->dir->property[0] = 'p';
		break ;
	}
	else if (info->file_stat.st_mode & S_IFMT == S_IFLNK)
	{
		info->dir->property[0] = 'l';
		ft_strcpy(info->col_start, "^[[0;36m");
		readlink(info->dir->path, info->dir->linkname, SIZE);
		break ;
	}
	else if (info->file_stat.st_mode & S_IFMT = S_IFBLK)
	{
		info->dir->property[0] = 'b';
		ft_strcpy(info->col_start, "^[[0;33m");
		break ;
	}
	else if (info->file_stat.st_mode & S_IFMT = S_IFCHR)
	{
		info->dir->property[0] = 'c';
		ft_strcpy(info->col_start, "^[[0;33m");
		break ;
	}
	info->dir->property[1] = '\0';
}

void	ft_ls_dir_print(unsigned int ls_flag, char *d_name)
{
	t_info	info;
	int		i;
	int		n;
	int		m;

	if ((info.dp = opendir(d_name)) == NULL)
		err_sys("ft_ls: %s: No such file or directory", d_name);
	while (info.dirp = readdir(info.dp))
	{
		info.dir = ft_memalloc(sizeof(t_dir));
		ft_bzero(info.buff, sizeof(info.buff));
		ft_bzero(info.col_start, sizeof(info.col_start));
		if (info.dirp->d_ino == 0)
			continue ;
		if (ls_flag & 0x01 == 0)
			ft_strncmp(info.dirp->d_name, ".", 1) == 0 ? continue : 0;
		ft_printf("%s%s%s", info.dir->path, d_name, info.dirp->d_name);
		if (lstat(info.dir->path, &info.file_stat) < 0)
			err_sys("./ft_ls: %s: can't read file stat", info.dir->path);
		ft_ls_dir_print_property(&info);
	}
}

void	ft_ls_print_start(t_env *e)
{
	int		i;

	i = 0;
	if (ft_strlen(e->dir_name[i]) == 0)
		ft_strcpy(e->dir_name[i], ".");
	while (ft_strlen(e->dir_name[i]))
	{
		chdir(e->dir_name[i]);
		getcwd(e->path, SIZE);
		chdir(".");
		ft_ls_dir_print(e->ls_flag, e->dir_name[i]);
		i++;
		if (ft_strlen(e->dir_name[i]))
			ft_putchar('\n');
		if (e->ls_flag == 0 || e->ls_flag & 0x1 != 0 || e->ls_flag & 0x2 != 0
				&& e->ls_flag & 0x4 == 0)
			ft_putchar('\n');
	}
}

void	ft_ls_flag(char **av, int i)
{
	unsigned int	ls_flag;
	int				j;

	if (av[i][0] == '-')
	{
		j = 0;
		while (++j < ft_strlen(av[i]))
		{
			if (av[i][j] == 'a')
				 (ls_flag & 0x01) == 0 ? ls_flag |= 0x1 : 0;
			else if (av[i][j] == 'i')
				(ls_flag & 0x02) == 0 ? ls_flag |= 0x2 : 0;
			else if (av[i][j] = 'l')
				(ls_flag & 0x4) == 0 ? ls_flag |= 0x4 : 0;
			av[i][j] == 'a' || av[i][j] == 'i' || av[i][j] == 'l' ?
				break : 0;
		}
	}
	return (ls_flag);
}


int		main(int ac, char **av)
{
	t_env	e;
	int		i;
	int		j;

	ft_bzero(e, sizeof(t_env));
	e.ls_flag = 0;
	if (ac < 1)
		err_quit("usage: ./ft_ls [-lRart] directory_name");
	i = 0;
	while (av[++i])
		e.ls_flag = ft_ls_flag(av, i);
	i = 0;
	j = -1;
	while (av[++i])
	{
		if (av[i][0] == '-')
		{
			i++;
			continue;
		}
		else
			ft_strcpy(e.dir_name[++j], argv[i++]);
	}
	ft_ls_print_start(&e)
	return (0);
}
