/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:43:52 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/24 13:46:42 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_child(t_shell *shell, t_node *index, int *fd_pipe)
{
	char	*full_path;

	default_child_signals();
	// if (!shell->tokens->next)
	// {
	// 	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	// 	// shell->exit_code = 258;
	// 	exit(258);
	// }
	if (index->cmd[0])
	{
		full_path = check_cmd_path(index->cmd[0], shell->path);
		path_check(shell, full_path, index->cmd[0]);
	}
	if (index->next != NULL)
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
	}
	if (index->files)
		open_redirect_files(shell, index);
	if (index->cmd[0])
		exec_check(shell, full_path, index->cmd, NULL);
	else
		exit(0);
}

void	execute_parent(t_node **index, int *fd_pipe)
{
	if ((*index)->next == NULL)
		close(STDIN_FILENO);
	else
	{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
	}
	*index = (*index)->next;
}

void	restore_std(int *tmpin, int *tmpout)
{
	dup2(*tmpin, STDIN_FILENO);
	close(*tmpin);
	dup2(*tmpout, STDOUT_FILENO);
	close(*tmpout);
}

void	create_pipe(t_shell *shell, t_node *index)
{
	if (index->next != NULL)
	{
		pipe(shell->fd_pipe);
		pipe_check(shell, shell->fd_pipe);
	}
}

void	execute(t_shell *shell)
{
	t_node	*index;
	int		pid;
	int		status;
	int		tmpin;
	int		tmpout;

	tmpout = dup(STDOUT_FILENO);
	tmpin = dup(STDIN_FILENO);
	index = shell->s_cmd;
	// print_char(shell->builtins);
	// if (ft_strncmp("echo", index->cmd[0], 4) == 0)
	// 	echo(index->cmd);
	// env(shell->env);
	// printf("*********************\n");
	// if (ft_strncmp("export", index->cmd[0], 6) == 0)
	// 	export(shell, index);
	// else
	// {
		heredoc(shell);
		// print_hd_names(shell);
		while (index)
		{
			ignore_signals();
			create_pipe(shell, index);
			pid = fork();
			fork_check(shell, pid);
			if (pid == 0)
				execute_child(shell, index, shell->fd_pipe);
			else
				execute_parent(&index, shell->fd_pipe);
		}
		restore_std(&tmpin, &tmpout);
		waitpid(pid, &status, 0);
		shell->exit_code = WEXITSTATUS(status);
	// }
	// env(shell->env);
}

