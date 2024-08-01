/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:06:11 by kkuhn             #+#    #+#             */
/*   Updated: 2024/07/29 13:41:25 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	openfile(char *filename, int mode, int is_here_doc)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK))
			return (STDIN);
		return (open(filename, O_RDONLY));
	}
	else if (is_here_doc == 0)
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666));
	else
		return (open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666));
}

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

void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = allocate_command(cmd);
	path = find_path(env, args[0]);
	if (path == 0)
	{
		free_paths(args);
		exit(127);
	}
	execve(path, args, env);
	exit(127);
}

void	redir(char *cmd, char **env, int fdin)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		if (fdin == STDIN)
			exit(1);
		else
			exec(cmd, env);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	int	fdin;
	int	fdout;
	int	is_here_doc;
	int	i;

	i = 3;
	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			is_here_doc = 1;
		else
			is_here_doc = 0;
		fdin = openfile(argv[1 + is_here_doc], INFILE, is_here_doc);
		fdout = openfile(argv[argc - 1], OUTFILE, is_here_doc);
		dup2(fdin, STDIN);
		dup2(fdout, STDOUT);
		redir(argv[2 + is_here_doc], envp, fdin);
		i += is_here_doc;
		while (i < argc - 2)
			redir(argv[i++], envp, 1);
		exec(argv[i], envp);
	}
	else
		ft_putstr_fd("Invalid number of arguments.\n", 2);
	return (1);
}
