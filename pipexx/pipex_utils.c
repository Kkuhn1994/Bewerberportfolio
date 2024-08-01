/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:47:00 by kkuhn             #+#    #+#             */
/*   Updated: 2024/07/31 13:43:34 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_short2(int *counter, char **cmd, char c)
{
	cmd[0]++;
	counter[0]++;
	while (cmd[0][0] != c)
		cmd[0]++;
	cmd[0]++;
}

int	count_parts(char *cmd)
{
	int	counter;
	int	is_word;

	is_word = 0;
	counter = 0;
	while (*cmd != 0)
	{
		if (*cmd != ' ' && *cmd != '\'' && *cmd != '"')
		{
			counter ++;
			while (*cmd != ' ' && *cmd != '\'' && *cmd != 0 && *cmd != '"')
				cmd ++;
		}
		if (*cmd == '\'')
			ft_short2(&counter, &cmd, '\'');
		if (*cmd == '"')
			ft_short2(&counter, &cmd, '"');
		if (*cmd == ' ')
			cmd ++;
	}
	return (counter);
}

char	*ft_str_safe(char **cmd, char c)
{
	int		j;
	char	*string;

	j = 0;
	while (cmd[0][j] != c && cmd[0][j] != 0)
		j++;
	string = malloc ((j + 1) * sizeof(char));
	j = 0;
	while (*cmd[0] != c && *cmd[0] != 0)
	{
		string[j] = *cmd[0];
		j ++;
		cmd[0]++;
	}
	string[j] = 0;
	return (string);
}

void	ft_short(int *i, char **commands, char **cmd, char c)
{
	cmd[0]++;
	commands[*i] = ft_str_safe(cmd, c);
	*i += 1;
	cmd[0]++;
}

char	*find_path(char *envp[], char *cmd)
{
	int		i;
	char	*path;
	char	*part_path;
	char	**paths;

	i = 0;
	if (ft_strnstr(&cmd[0], ".sh", ft_strlen(&cmd[0])) != 0
		|| ft_strnstr(&cmd[0], "/", ft_strlen(&cmd[0])) != 0)
		return (ft_remove_space(&cmd[0]));
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i ++;
	paths = ft_split(&envp[i][5], ':');
	i = -1;
	while (paths[++ i] != 0)
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_paths(paths), path);
		free(path);
	}
	free_paths(paths);
	return (0);
}
