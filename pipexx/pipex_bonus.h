/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:47:55 by kkuhn             #+#    #+#             */
/*   Updated: 2024/06/21 19:47:56 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define INFILE 0
# define OUTFILE 1

void	ft_short2(int *counter, char **cmd, char c);
int		count_parts(char *cmd);
void	ft_short(int *i, char **commands, char **cmd, char c);
char	**allocate_command(char *cmd);
char	**cmd_in_folder(char *cmd);
void	error(char *errormessage, int exitcode);
void	error2(char *errormessage, int exitcode);
void	free_paths(char **paths);
char	*ft_remove_space(char *cmd);
char	*ft_str_safe(char **cmd, char c);
int		openfile(char *filename, int mode, int is_here_doc);
char	*find_path(char *envp[], char *cmd);

#endif