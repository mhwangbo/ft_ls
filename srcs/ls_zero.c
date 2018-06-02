/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_zero.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 18:36:21 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/06/01 19:07:26 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_zero_printer(t_env *e, int no_print, int no_dir, int j)
{
	int		i;
	int		k;
	int		dir_line;
	int		line_counter;

	line_counter = 0;
	if (no_dir > 1)
		ft_printf("%s:\n", e->t[j].dir_name);
	dir_line = no_print;
	while ((e->t[j].space * dir_line) > e->win_size.ws_col)
		dir_line--;
	line_counter = no_print / dir_line;
	i = -1;
	while (++i < line_counter)
	{
		k = -1;
		while (++k < dir_line)
			ft_printf("%-*s", e->t[j].space + 1, e->t[j].order[i + (k * line_counter)]);
		ft_printf("\n");
	}
	if (no_dir > 1 && j != no_dir - 1)
		ft_printf("\n");
}

void	ls_zero(t_env *e, int no_dir)
{
	int		i;
	int		j;
	int		h;
	int		no_print;

	j = -1;
	while (++j < no_dir)
	{
		i = -1;
		no_print = 0;
		e->t[j].space = 0;
		while (++i < e->t[j].max_dir)
			if (e->t[j].dp[i]->d_name[0] != '.')
			{
				e->t[j].space < ft_strlen(e->t[j].dp[i]->d_name) ?
					e->t[j].space = ft_strlen(e->t[j].dp[i]->d_name) : 0;
				no_print++;
			}
		e->t[j].order = malloc(sizeof(char*) * no_print);
		h = 0;
		i = 0;
		while (h < no_print && i < e->t[j].max_dir)
		{
			if (e->t[j].dp[i]->d_name[0] != '.')
				e->t[j].order[h++] = e->t[j].dp[i]->d_name;
			i++;
		}
		ls_alpha_order(e->t[j].order, no_print);
		ls_zero_printer(e, no_print, no_dir, j);
	}
}
