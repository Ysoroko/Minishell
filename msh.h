/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 11:31:41 by ablondel          #+#    #+#             */
/*   Updated: 2021/07/22 17:24:36 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define NONE 0
# define RLSIMPLE 1
# define RRSIMPLE 2
# define RLDOUBLE 3
# define RRDOUBLE 4
# define EXECUTABLE 5
# define OPTION 6
# define ARGUMENT 7
# define VARIABLE 8
# define READABLE 9
# define WRITABLE 10
# define PERMITTED 11
# define KEYWORD 12

typedef struct  s_msh
{
	char		**strs;
	char		**piped;
	char		**paths;
	int			**types;
	char		*s;
	char		c;
	int			limit;
	int			i;
	int			j;
	int			k;
}               t_msh;

#endif