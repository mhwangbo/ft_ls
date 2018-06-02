/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:15:13 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/06/01 22:30:32 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "../lib/libft/includes/ft_printf.h"
# include "../lib/libft/includes/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <time.h>

typedef struct		s_dir
{
	int				max_dir;
	struct dirent	**dp;
	struct stat		*detail;
	char			*dir_name;
	char			**order;
	size_t			space;
}					t_dir;

typedef struct		s_env
{
	int				flag[6];
	t_dir			*t;
	struct winsize	win_size;
}					t_env;

/*
** ls_main.c
*/
int					main(int ac, char **av);
void				ls_flags(int ac, char **av);
void				ls_flags_support(int ac, char **av, t_env *e, int i);
void				ls_flags_send(t_env *e, int no_dir);

/*
** ls_dir_read.c
*/
void				ls_flags_read(int ac, char **av, t_env *e, int i);
void				read_dir(t_dir *e);
void				ls_alpha_order(char **order, int no_print);

/*
** ls_zero.c
*/
void				ls_zero(t_env *e, int no_dir);
void				ls_zero_printer(t_env *e, int no_print, int no_dir, int j);

/*
** ls_two.c
*/
void				ls_two(t_env *e, int no_dir);
#endif
