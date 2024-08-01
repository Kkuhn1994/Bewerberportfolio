/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:48:13 by kkuhn             #+#    #+#             */
/*   Updated: 2024/07/29 18:58:40 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *errormessage, int exitcode)
{
	ft_putstr_fd("", 1);
	ft_putstr_fd(errormessage, 2);
	free(errormessage);
	exit(exitcode);
}

void	error2(char *errormessage, int exitcode)
{
	char	*error_msg;

	error_msg = ft_strjoin("pipex: ", errormessage);
	free(errormessage);
	error(error_msg, exitcode);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != 0)
	{
		free(paths[i]);
		i ++;
	}
	free(paths);
}

char	*ft_remove_space(char *cmd)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (cmd[i + j] != 0)
	{
		if (cmd[i + j] == ' ')
			j ++;
		if (cmd[i + j] == '\"')
			cmd[i] = '\"';
		else
			cmd[i] = cmd[i + j];
		i ++;
	}
	cmd[i + j] = 0;
	return (cmd);
}

char	**cmd_in_folder(char *cmd)
{
	char	**command;

	command = malloc (2 * sizeof(char *));
	command[0] = ft_strdup(cmd);
	command[1] = 0;
	return (command);
}
