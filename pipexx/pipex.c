/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:17:44 by kkuhn             #+#    #+#             */
/*   Updated: 2024/07/31 20:24:16 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**allocate_command(char *cmd)
{
	char	**commands;
	int		nr_commands;
	int		i;

	if (ft_memcmp(cmd, "./", 2) == 0)
		return (cmd_in_folder(cmd));
	nr_commands = count_parts(cmd) + 1;
	commands = malloc (nr_commands * sizeof(char *));
	i = 0;
	while (i < nr_commands - 1)
	{
		if (*cmd != ' ' && *cmd != '\'' && *cmd != '"')
		{
			commands[i] = ft_str_safe(&cmd, ' ');
			i ++;
		}
		if (*cmd == '\'')
			ft_short(&i, commands, &cmd, '\'');
		else if (*cmd == '"')
			ft_short(&i, commands, &cmd, '"');
		else if (*cmd == ' ')
			cmd ++;
	}
	commands[nr_commands - 1] = 0;
	return (commands);
}

void	childprocess(int *pipe_fd, char *argv[], char *envp[], int *statuscode)
{
	char	*path;
	char	**cmd;
	int		fd_open;

	close(pipe_fd[0]);
	cmd = allocate_command(argv[2]);
	if (cmd == 0)
		error("command split failed", 127);
	path = find_path(envp, cmd[0]);
	if (path == 0)
		error3(cmd);
	fd_open = open(argv[1], O_RDONLY, 0777);
	if (dup2(fd_open, STDIN_FILENO) == -1)
		error(ft_strdup("duplication failed"), 127);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error(ft_strdup("duplication failed"), 127);
	close(pipe_fd[1]);
	close(fd_open);
	if (execve(path, cmd, envp) == -1)
		error(ft_strdup("execution of command failed"), 127);
}

int	endprocess(int *pipe_fd, char *argv[], char *envp[], int *data)
{
	int		fd_write;
	char	*path;
	char	**cmd;

	close(pipe_fd[1]);
	cmd = allocate_command(argv[data[1] - 2]);
	if (cmd == 0)
		error(ft_strdup("command split failed"), 127);
	fd_write = open(argv[data[1] - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_write == -1)
		error(ft_strdup("open output file failed"), 127);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		error(ft_strdup("duplication failed"), 127);
	if (dup2(fd_write, STDOUT_FILENO) == -1)
		error(ft_strdup("duplication failed"), 127);
	close(pipe_fd[0]);
	close(fd_write);
	path = find_path(envp, cmd[0]);
	if (path == 0)
		error3(cmd);
	if (execve(path, cmd, envp) == -1)
		error(ft_strdup("execution of command failed"), 127);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	pid_t	pid2;
	int		pipe_fd[2];
	int		data[4];

	data[0] = 0;
	data[1] = argc;
	if (argc < 5 || argc > 5)
		error(ft_strdup("not enough arguments"), 127);
	if (pipe(pipe_fd) == -1)
		error(ft_strdup("pipe not working"), 127);
	pid = fork();
	if (pid == -1)
		error(ft_strdup("fork failed"), 127);
	if (pid == 0)
		childprocess(pipe_fd, argv, envp, &data[0]);
	pid2 = fork();
	if (pid2 == -1)
		error(ft_strdup("fork failed"), 127);
	if (pid2 == 0)
		endprocess(pipe_fd, argv, envp, data);
	wait(&data[0]);
	exit(data[0]);
}
