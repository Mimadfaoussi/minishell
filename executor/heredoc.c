/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaoussi <mfaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:32:10 by anamieta          #+#    #+#             */
/*   Updated: 2024/05/30 17:11:18 by mfaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	delimiter_is_met(t_token *files, char *line)
{
	if (ft_strlen(line) == ft_strlen(files->next->content))
	{
		if (ft_strncmp(line, files->next->content, ft_strlen(line)) == 0)
		{
			free(line);
			return (1);
		}
	}
	return (0);
}

void	heredoc_norm(t_shell *shell, t_token *files, char *line, int *fd)
{
	char	*expanded;

	if (files->hd_expanded == 0)
	{
		expanded = expand(line, shell);
		if (expanded)
		{
			write(*fd, expanded, ft_strlen(expanded));
			free(expanded);
		}
	}
	else
		write(*fd, line, ft_strlen(line));
	write(*fd, "\n", 1);
}

void	heredoc_loop(t_token *files, int *fd, t_shell *shell)
{
	char	*line;
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		heredoc_signals();
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (delimiter_is_met(files, line) == 1)
				break ;
			else
				heredoc_norm(shell, files, line, fd);
			free(line);
		}
		exit(1);
	}
	else
		waitpid(pid, &status, 0);
}

void	heredoc(t_shell *shell)
{
	t_node	*s_cmd;
	t_token	*files;
	int		count;
	int		fd;

	count = 0;
	s_cmd = shell->s_cmd;
	ignore_signals();
	while (s_cmd)
	{
		files = s_cmd->files;
		while (files)
		{
			if (files->type == HEREDOC)
			{
				assign_name(&files, &count);
				fd = open_file_hd(shell, files->type, files->hd_name);
				heredoc_loop(files, &fd, shell);
				close(fd);
			}
			files = files->next;
		}
		s_cmd = s_cmd->next;
	}
}

void	assign_name(t_token **file, int *count)
{
	t_token	*index;
	int		i;

	index = *file;
	i = 0;
	while (i < 12)
	{
		index->hd_name[i] = '\0';
		i++;
	}
	index->hd_name[0] = '.';
	index->hd_name[1] = '/';
	index->hd_name[2] = 't';
	index->hd_name[3] = 'm';
	index->hd_name[4] = 'p';
	index->hd_name[5] = '/';
	index->hd_name[6] = 'f';
	index->hd_name[7] = 'i';
	index->hd_name[8] = 'l';
	index->hd_name[9] = 'e';
	index->hd_name[10] = *count + '0';
	*count = *count + 1;
}
