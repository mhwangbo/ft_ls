/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 18:48:19 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/06/01 22:30:29 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
 ** 0 = no flags, 1 = -l, 2 = -R, 3 = -a, 4 = -r, 5 = -t
 ** -l: list: long format. before listing, total sum of all file size displays
 ** -R: Recursively list subdirectories encountered.
 ** -a: Include directory entries whos names begin with a dot (.).
 ** -r: Reverse the order of the sort to get reverse lexicographical
 **      order or oldest entries first (or largest files last, if combined
 **      with sort by size)
 ** -t: Sort by time modified (most recently modified first)
 */

void	ls_flags_send(t_env *e, int no_dir)
{
	if (e->flag[2] == 1)
		ls_two(e, no_dir);
	else if (e->flag[0] == 1)
		ls_zero(e, no_dir);
}

void	ls_flags_support(int ac, char **av, t_env *e, int i)
{
	int		k;

	e->t = ft_memalloc(sizeof(t_dir) * (ac != 1 ? (ac - i) : 1));
	ls_flags_read(ac, av, e, i);
	ls_flags_send(e, (ac == 1 ? ac : ac - i));
	k = -1;
	while (++k < (ac == 1 ? ac : (ac - 1)))
	{
		if (ac == 1 || ac == i)
			free(e->t[k].dir_name);
		free(e->t[k].detail);
		free(e->t[k].dp);
		free(e->t[k].order);
	}
	free(e->t);
}

void	ls_flags(int ac, char **av)
{
	t_env	e;
	int		i;
	int		j;

	i = 0;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &e.win_size);
	ft_bzero(e.flag, sizeof(int) * 6);
	while (++i < ac && av[i][0] == '-')
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
	if (e.flag[1] == 0 && e.flag[3] == 0 && e.flag[4] == 0 && e.flag[5] == 0)
		e.flag[0] = 1;
	ls_flags_support(ac, av, &e, i);
}

int		main(int ac, char **av)
{
	if (ac < 1)
		return (0);
	ls_flags(ac, av);
	//	while (1);
	return (0);
}
