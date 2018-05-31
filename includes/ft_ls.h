/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:15:13 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/31 00:34:55 by mhwangbo         ###   ########.fr       */
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
# include <time.h>

typedef struct		s_dir
{
	int				max_dir;
	struct dirent	**dp;
	struct stat		*detail;
	char			*dir_name;
}					t_dir;

typedef struct		s_env
{
	int				flag[6];
	t_dir			*t;
}					t_env;

#endif
