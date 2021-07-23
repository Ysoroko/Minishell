/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 19:30:43 by ablondel          #+#    #+#             */
/*   Updated: 2021/06/29 17:46:23 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

typedef struct s_pipex
{
	char		*s;
	char		**strs;
	char		**paths;
	char		*tmp;
	char		*flush;
	int			res;
	int			i;
	int			j;
	int			k;
	char		*infile;
	char		*outfile;
	int			pfd[2];
	int			file1;
	int			file2;
	pid_t		p1;
	pid_t		p2;
	char		**args1;
	char		**args2;
}				t_pipex;

char			*ft_memzero(unsigned int len);
unsigned int	ft_len(char *s);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(char *src);
int				ft_nb_paths(char *s);
char			**ft_free_tab(char **strs);
char			**ft_split(t_pipex *add);
int				ft_strcmp(char *s1, char *s2, int n);
char			*ft_set_all_paths(t_pipex *add, char **env);
void			ft_print_error(char *error, t_pipex *add);
void			ft_check_permissions(t_pipex *add, char **av);
int				ft_nb_options(char *s);
char			**ft_split_arg(char *s, t_pipex *add);
char			*ft_setup_args(t_pipex *add, char **av, char **env);
char			*ft_child_one(t_pipex *add);
char			*ft_child_two(t_pipex *add);
void			ft_parent(t_pipex *add);

#endif
