/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 11:31:41 by ablondel          #+#    #+#             */
/*   Updated: 2021/07/21 19:29:09 by ablondel         ###   ########.fr       */
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

typedef struct  s_msh
{
	char		**strs;
	char		**paths;
	char		*s;
	char		c;
	int			limit;
	int			i;
	int			j;
	int			k;
}               t_msh;

#endif