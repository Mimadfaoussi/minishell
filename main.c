/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:05:57 by mfaoussi          #+#    #+#             */
/*   Updated: 2024/05/24 16:37:15 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;

	if (argc != 1 || *argv == NULL)
		return (2);
	shell_init(&shell, envp);
	// env(shell.env);
	// unset(&(shell.env), "PATH");
	// printf("break \n\n\n\n\n\n");
	// env(shell.env);
	while (1)
	{
		setup_signals();
		line = readline("$ ");
		if (!line)
			break ;
		if (ft_strncmp("exit", line, 4) == 0)
			return (0);
		else
		{
			if (check_quotes(line) == 0 && redirection_correct(line) == 0)
			{
				shell_setup(&shell, line);
				execute(&shell);
				clean_nodes(&(shell.s_cmd));
				clean_path(&shell);
			}
			else if (check_quotes(line) == 1)
			{
				shell.exit_code = 1;
				printf("Quotes error!\n");
			}
			else if (redirection_correct(line) == 1)
			{
				shell.exit_code = 258;
				printf("minishell: syntax error near unexpected token\n");
			}
			add_history(line);
			free(line);
			// printf("****** checking env update ****");
			// env(shell.env);
		}
	}
	return (0);
}

