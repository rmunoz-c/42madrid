/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-12 16:12:12 by rmunoz-c          #+#    #+#             */
/*   Updated: 2024-12-12 16:12:12 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file, size_t b)
{
	int	n;

	if (b == 0)
		n = open(file, O_RDONLY, 0644);
	else if (b == 1)
		n = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		return (-1);
	if (n == -1)
		ft_error("Error opening file\n", TRUE);
	return (n);
}

void	exec(char *cmd, char **envp)
{
	char	*path;
	char	**split_cmd;

	split_cmd = ft_split(cmd, ' ');
	path = ft_path(split_cmd[0], envp);
	if (execve(path, split_cmd, envp) == -1)
	{
		ft_error("Error executing command\n", FALSE);
		ft_putendl_fd(split_cmd[0], 2);
		ft_free_array(split_cmd);
		exit(EXIT_FAILURE);
	}
}

void	child_process(char **argv, int *pipe_fd, char **envp)
{
	int	fd_in;
	int fd_out;

	fd_in = open_file(argv[1], 0);
	dup2(fd_in, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	exec(argv[2], envp);
	fd_out = open_file(argv[4], 1);
	dup2(fd_out, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	exec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	child;
	pid_t	child2;
	int		i;

	if (argc != 5)
		ft_error("Error: Try with ./pipex infile cmd1 cmd2 outfile\n", TRUE);
	if (pipe(pipe_fd) < 0)
		ft_error("Error creating pipe\n", TRUE);
	child = fork();
	if (child < 0)
		ft_error ("Error forking process\n", TRUE);
	if (child == 0)
		child_process(argv, pipe_fd, envp);
	child2 = fork();
	if (child2 < 0)
		ft_error ("Error forking process\n", TRUE);
	if (child2 == 0)
		child_process(argv, pipe_fd, envp);
	i = 0;
	while (i < 2)
	{
		wait(NULL);
		i++;
	}
}