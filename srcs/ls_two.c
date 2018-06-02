/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_two.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 18:37:16 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/06/01 22:30:28 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_two(t_env *e, int no_dir)
{
	int		i;
	int		j;
	int		h;
	int		max_sub_dir;
	char	*tmp;
	char	**sub_dir;
	t_env	sub_e;

	i = -1;
	e->flag[2] = 0;
	while (++i < no_dir)
	{
		j = -1;
		max_sub_dir = 0;
		while (++j < e->t[i].max_dir)
		{
			ft_printf("%s [%d]\n", e->t[i].dp[j]->d_name, e->t[i].detail[j].st_mode);
			if (e->t[i].detail[j].st_mode == 16877)
				max_sub_dir++;
		}
		ft_printf("%d\n", max_sub_dir);
		sub_dir = ft_memalloc(sizeof(char*) * max_sub_dir);
		j = -1;
		h = 0;
		while (++j < e->t[i].max_dir)
		{
			if (e->t[i].dp[j]->d_type == 4)
			{
				tmp = ft_strjoin(e->t[i].dir_name, "/");
				sub_dir[h++] = ft_strjoin(tmp, e->t[i].dp[j]->d_name);
				free(tmp);
			}
		}
		sub_e = *e;
		ls_flags_support(max_sub_dir, sub_dir, &sub_e, 1);
	}
}
