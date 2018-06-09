/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:33:56 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/06/08 22:09:10 by mhwangbo         ###   ########.fr       */
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
	DIR				*dp;
	struct dirent	*dir;
	struct stat		stat;
	char			**dir_name;
	int				depth;
}					t_dir;

typedef struct		s_env
{
	int				ac;
	int				flag[6];
	char			**position;
}					t_env;

#endif
